import can

class CanTransceiver:    
    def __init__(self, CanDevice='usb2can', serial='51906A2C', baudrate='500'):
        #Initialise the Korlan Can device
        self.CanDevice = CanDevice
        self.SerialNo  = serial
        self.BaudRate  = baudrate
        self.dll       = '.\\drivers\\dll\\usb2can.dll'
        
    def __del__(self):
        print("[KORLAN][I] Bye bye")
            
    def CreateMessage(self, CanId=0x000, CanData=[0,0,0,0,0,0,0,0]):
        CanMsg = can.Message(arbitration_id=CanId, data=CanData)
        
        return(CanMsg)

    def SendCanMsg(self, TxCanMsg):
        try:
            with can.interface.Bus(interface=self.CanDevice, serial=self.SerialNo, bitrate=self.BaudRate*1000, dll=self.dll) as bus:
                bus.send(TxCanMsg)
                return(True)
        except:
            return(False)
                
    def GetCanMsg(self, RxCanMsg):
        try:
            with can.interface.Bus(interface=self.CanDevice, serial=self.SerialNo, bitrate=self.BaudRate*1000, dll=self.dll) as bus:
                RxCanMsg = bus.recv(1)
            
                if RxCanMsg is not None:
                    return(RxCanMsg)
                else:
                    return(None)
        except:
            return(None)
                
    def SendTxMsgPeriodic(self, msg, cycle_time):
        try:
            with can.interface.Bus(interface=self.CanDevice, serial=self.SerialNo, bitrate=self.BaudRate*1000, dll=self.dll) as bus:
                bus.send_periodic(msg, cycle_time)
                return(True)
        except:
            print("[KORLAN] Korlan - Unable to connect")
            return(False)
