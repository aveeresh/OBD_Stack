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
        return(SerialData)
        
    def WriteSerialData(self, SerialData):        
        try:
            self.SerialHandle.write(SerialData)
            self.SerialHandle.flush()
                
            return(True)
        except:
            return(False)
                          
    def CreateMessage(self, CanId=None, CanData=[0,0,0,0,0,0,0,0]):
        CanMsg = can.Message(arbitration_id=CanId, data=CanData)
        
        return(CanMsg)

    def SendCanMsg(self, TxCanMsg):
        SerialData = self.AssembleSerialData(TxCanMsg.arbitration_id, TxCanMsg.data)
        
        return(self.WriteSerialData(SerialData))
                
    def GetCanMsg(self, RxCanMsg):
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
                
    def SendTxMsgPeriodic(self, msg, cycle_time):
        with can.interface.Bus(interface=self.CanDevice, bitrate=self.BaudRate*1000) as bus:
            bus.send_periodic(msg, cycle_time)
