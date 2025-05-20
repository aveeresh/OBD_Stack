
import serial
import can

class CanTransceiver:
    
    def __init__(self, ComPort=None, SerialBaudRate=2000000, DataBits=serial.EIGHTBITS, StopBits=serial.STOPBITS_ONE, ParityType=serial.PARITY_NONE):
        #Store the settings for the WAVESHARE_A USB2CAN device
        print("[WAVESHARE_A][I] Connecting to %s at %d bps" % (ComPort,SerialBaudRate))
        
        self.ComPort = ComPort
        
        try:
            self.SerialHandle = serial.Serial(port=ComPort, baudrate=SerialBaudRate, bytesize=DataBits, parity=ParityType, stopbits=StopBits, timeout=1)
            self.ConnectActive = True
        except:
            print("[WAVESHARE_A][E] Unable to open %s" % ComPort)
            self.ConnectActive = False
                
    def __del__(self):
        if self.ConnectActive==True:
            self.SerialHandle.close()
        
        print("[WAVESHARE_A][I] Bye bye")
        
    def AssembleSerialData(self, CanId, CanData):
        SerialData = [0xAA, (0xC0|len(CanData))]
        #extract the lower 8-bit of the Can Id
        SerialData.append( (CanId & 0xFF) )
        #Extract the bits 8-11 of the Can Id
        SerialData.append( (CanId & 0xF00)>>8 )
        
        for byte in CanData:
            SerialData.append(byte)
            
        SerialData.append(0x55)
         
        #print(bytearray(SerialData))
        return (SerialData)
        
    def WriteSerialData(self, SerialData):        
        try:
            self.SerialHandle.write(SerialData)
            self.SerialHandle.flush()
                
            return(True)
        except:
            return(False)
                          
    def CreateMessage(self, CanId=None, CanData=None):
        CanData = CanData or [0] * 64
        CanMsg = can.Message(arbitration_id=CanId, data=CanData)
        return(CanMsg)

    def SendCanMsg(self, TxCanMsg):
        SerialData = self.AssembleSerialData(TxCanMsg.arbitration_id, TxCanMsg.data)
        #print(SerialData)
        #print(self.WriteSerialData(SerialData))
        return(self.WriteSerialData(SerialData))
                
    def GetCanMsg(self, RxCanMsg):
        try:
            Data = self.SerialHandle.read(14)
            Data = list(Data)
            
            if len(Data)!=13:
                return(None)
            else:        
                #Check whether a valid serial data frame received
                if Data[0]!=0xAA or Data[len(Data)-1]!=0x55:
                    RxCanMsg = None
                else:
                    #Valid serial data frame, extract data 
                    RxCanMsg = self.CreateMessage()
                    RxCanMsg.arbitration_id = (Data[3]<<8 | Data[2])
                    for i in range(0,7):
                        RxCanMsg.data[i] = Data[4+i]
                
                #print(RxCanMsg)
                return(RxCanMsg)
        except:
            return(None)
                
    def SendTxMsgPeriodic(self, msg, cycle_time):
        with can.interface.Bus(interface=self.CanDevice, bitrate=self.BaudRate*1000) as bus:
            bus.send_periodic(msg, cycle_time)
            
            
    def GetTPCanMsg(self):
        try:
            full_data = []
            data_length = 0
            next_seq_num = 1

            while True:
                received_data = self.SerialHandle.read(13)
                received_data = list(received_data)
                print(received_data)
                if len(received_data) != 13 or received_data[0] != 0xAA or received_data[len(received_data)-1] != 0x55:
                    #print("Invalid frame")
                    return(None)  #invalid frame

                pci_byte = received_data[4]
                #print(pci_byte)
                
                data_bytes = received_data[5:11]  #7 data bytes
                arb_id = (received_data[3] << 8) | received_data[2]
                
                # Single Frame (SF)
                if(pci_byte & 0xF0) == 0x00:
                    data_length = pci_byte & 0x0F
                    RxCanMsg = self.CreateMessage()
                    RxCanMsg.arbitration_id = (received_data[3]<<8 | received_data[2])
                    
                    total_data = received_data[4 : 5 + data_length]  # PCI + actual data
                    RxCanMsg.data[:len(total_data)] = total_data
                    RxCanMsg.data = RxCanMsg.data[:len(total_data)]
                    
                    print(list(RxCanMsg.data[:data_length]))
                    return RxCanMsg

                
                # First Frame 
                elif(pci_byte & 0xF0) == 0x10:
                    data_length = ((pci_byte & 0x0F) << 8) | data_bytes[0]
                    #RxCanMsg = self.CreateMessage()
                    #RxCanMsg.arbitration_id = (received_data[3]<<8 | received_data[2])
                    full_data = received_data[5 : 12]
                    print(list(full_data))
                    continue
                
                # Consecutive Frame 
                elif (pci_byte & 0xF0) == 0x20:
                    seq_num = pci_byte & 0x0F
                    if seq_num != next_seq_num:
                        print(f"Sequence number mismatch. Expected {next_seq_num}, got {seq_num}")
                        return None
                    next_seq_num = (next_seq_num + 1) % 16
                    full_data.extend(received_data[5:12])

                    if len(full_data) >= data_length + 1:  # +1 for PCI from First Frame
                        RxCanMsg = self.CreateMessage()
                        RxCanMsg.arbitration_id = (received_data[3] << 8) | received_data[2]
                        RxCanMsg.data[:data_length + 1] = full_data[:data_length + 1]
                        RxCanMsg.data = RxCanMsg.data[:data_length + 1]
                        print(list(RxCanMsg.data))
                        return RxCanMsg

                else:
                    continue  
                
        except:
            return None

