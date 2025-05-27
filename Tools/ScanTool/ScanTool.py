import sys
sys.path.insert(1, ".\\drivers\\korlan\\")
sys.path.insert(1, ".\\drivers\\pcan\\")
sys.path.insert(1, ".\\drivers\\waveshare\\")

import threading
import serial
import random
import json

import korlan
import waveshare_a

from PyQt5.QtWidgets import (
    QApplication, QDialog, QMainWindow, QMessageBox, QTableWidgetItem, QHeaderView
)
from PyQt5 import QtWidgets
from PyQt5.uic import loadUi
from PyQt5.QtCore import QThread

from MainWindow import Ui_MainWindow
from Settings import Ui_Settings

class Window(QMainWindow, Ui_MainWindow):
    MSG_DISPLAY_TIME = 5000
    P2_TIME_MS = 5
    SETTINGS_FILE = "settings.json"

    def __init__(self, parent=None):
        super().__init__(parent)
        self.setupUi(self)

        self.ConnectSignalsSlots()

        self.MeasureActive = False
        self.ConnectStatus = False

        self.InitDashboard();

        self.ThreadHandle = threading.Timer(0.5, self.CyclicTask, args = ())
        self.ThreadHandle.start()

    def __del__(self):
        try:
            self.ThreadHandle.cancel()
        except:
            print("[SCAN TOOL][E] Runtime error")

    def InitDashboard(self):
        print("[SCAN TOOL][I] Initialising Scan tool")

        self.SetupGUIData()

        self.GetSettings()

        DefaultReqId = self.JsonData['default_tester_req']['request_id']
        DefaultReqData = self.JsonData['default_tester_req']['request_data']

        self.lineEdit_ReqId.setText(DefaultReqId)
        self.lineEdit_ReqData.setText(DefaultReqData)

        header = self.DTCList.horizontalHeader()
        header.setSectionResizeMode(0, QHeaderView.ResizeToContents)
        header.setSectionResizeMode(1, QHeaderView.ResizeToContents)

    def SetupGUIData(self):
        #Mode $01 data
        self.Mode_01_PIDList = [0x04, 0x05, 0x0C, 0x22, 0x2C, 0x31]
        self.LE_RawValList = [
            self.lineEdit_RawVal_PID_04,
            self.lineEdit_RawVal_PID_05,
            self.lineEdit_RawVal_PID_0C,
            self.lineEdit_RawVal_PID_22,
            self.lineEdit_RawVal_PID_2C,
            self.lineEdit_RawVal_PID_31
        ]
        self.LE_PhyValList = [
            self.lineEdit_PhyVal_PID_04,
            self.lineEdit_PhyVal_PID_05,
            self.lineEdit_PhyVal_PID_0C,
            self.lineEdit_PhyVal_PID_22,
            self.lineEdit_PhyVal_PID_2C,
            self.lineEdit_PhyVal_PID_31,
        ]
       

        self.CB_SuppPIDList = [
        self.checkBox_01,
        self.checkBox_02,
        self.checkBox_03,
        self.checkBox_04,
        self.checkBox_05,
        self.checkBox_06,
        self.checkBox_07,
        self.checkBox_08,
        self.checkBox_09,
        self.checkBox_0A,
        self.checkBox_0B,
        self.checkBox_0C,
        self.checkBox_0D,
        self.checkBox_0E,
        self.checkBox_0F,
        self.checkBox_10,
        self.checkBox_11,
        self.checkBox_12,
        self.checkBox_13,
        self.checkBox_14,
        self.checkBox_15,
        self.checkBox_16,
        self.checkBox_17,
        self.checkBox_18,
        self.checkBox_19,
        self.checkBox_1A,
        self.checkBox_1B,
        self.checkBox_1C,
        self.checkBox_1D,
        self.checkBox_1E,
        self.checkBox_1F,
        self.checkBox_20,
        ]
        self.PIDDetails = [
            #PID $04
            {
                'num_bytes' : 1,
                'offset'    : 0,
                'factor'    : 2.55
            },
            #PID $05
            {
                'num_bytes' : 1,
                'offset'    : -40,
                'factor'    : 1
            },
            #PID $0C
            {
                'num_bytes' : 2,
                'offset'    : 0,
                'factor'    : 4
            },
            #PID $22
            {
                'num_bytes' : 2,
                'offset'    : 0,
                'factor'    : 12.65
            },
            #PID $2C
            {
                'num_bytes' : 1,
                'offset'    : 0,
                'factor'    : 2.55
            },
            #PID $31
            {
                'num_bytes' : 2,
                'offset'    : 0,
                'factor'    : 1
            }
        ]

        self.Mode_09_PIDDetails = [
            #PID $01
            {
                'num_bytes' : 1,
                'type'      : 'number'
            },
            #PID $02
            {
                'num_bytes' : 17,
                'type'      : 'ascii'
            },
            #PID $04
            {
                'num_bytes' : 16,
                'type'      : 'ascii'
            },
  		]

    def ConnectSignalsSlots(self):
        self.actionConnect.triggered.connect(self.Connect)
        self.actionDisconnect.triggered.connect(self.Disconnect)
        self.actionSettings.triggered.connect(self.OnClickSettings)
        self.actionExit.triggered.connect(self.Exit)
        self.actionStart.triggered.connect(self.StartMeasurement)
        self.actionStop.triggered.connect(self.StopMeasurement)
        self.actionAbout.triggered.connect(self.About)

        self.radioButton_00_20.toggled.connect(self.UpdateSuppPIDDisplay)
        self.radioButton_20_40.toggled.connect(self.UpdateSuppPIDDisplay)
        self.radioButton_40_60.toggled.connect(self.UpdateSuppPIDDisplay)
        self.radioButton_60_80.toggled.connect(self.UpdateSuppPIDDisplay)
        self.radioButton_80_A0.toggled.connect(self.UpdateSuppPIDDisplay)
        self.radioButton_A0_C0.toggled.connect(self.UpdateSuppPIDDisplay)
        self.radioButton_C0_E0.toggled.connect(self.UpdateSuppPIDDisplay)

        self.PB_SendReq.clicked.connect(self.On_General_Send_Btn_Click)

    def OnClickSettings(self, SettingsFile):
        self.dialog = Settings(self.SETTINGS_FILE);
        self.dialog.exec()

    def StartMeasurement(self):
        if self.ConnectStatus==True:
            if self.MeasureActive==False:
                self.MeasureActive = True
                self.statusbar.showMessage("MEASUREMENT - Started", self.MSG_DISPLAY_TIME)
            else:
                self.statusbar.showMessage("MEASUREMENT - Already active", self.MSG_DISPLAY_TIME)
        else:
            self.statusbar.showMessage("CAN LOGGER - Not connected", self.MSG_DISPLAY_TIME)

    def StopMeasurement(self):
        if self.ConnectStatus==True:
            if self.MeasureActive==True:
                self.MeasureActive = False
                self.statusbar.showMessage("MEASUREMENT - Stopped", self.MSG_DISPLAY_TIME)
            else:
                self.statusbar.showMessage("MEASUREMENT - not active", self.MSG_DISPLAY_TIME)
        else:
            self.statusbar.showMessage("CAN LOGGER - Not connected", self.MSG_DISPLAY_TIME)

    def CyclicTask(self):
        try:
            while True:
                if self.MeasureActive==True:
                    #print("Cyclic task called")
                    CurrentTab = self.tabWidget.tabText(self.tabWidget.currentIndex())

                    #print(CurrentTab)

                    if CurrentTab=='Mode_01':
                        self.ProcessMode_01()
                    elif CurrentTab=='Mode_03':
                        self.ProcessMode_03()
                    elif CurrentTab=='Mode_09':
                        self.ProcessMode_09()
                    elif CurrentTab=='Mode_01_Supp_PIDs':
                        self.UpdateSuppPIDDisplay()
        except RuntimeError as e:
            print("[SCAN TOOL][E] Runtime error")
            exit(0)

    def UpdateSuppPIDDisplay(self):
        if self.radioButton_00_20.isChecked():
            PID = 0x00
        elif self.radioButton_20_40.isChecked():
            PID = 0x20
        elif self.radioButton_40_60.isChecked():
            PID = 0x40
        elif self.radioButton_60_80.isChecked():
            PID = 0x60
        elif self.radioButton_80_A0.isChecked():
            PID = 0x80
        elif self.radioButton_A0_C0.isChecked():
            PID = 0xA0
        elif self.radioButton_C0_E0.isChecked():
            PID = 0xC0
        else:
            PID = 0x00
            self.radioButton_00_20.setChecked(True)

        #end tester request
        RespMsg = self.TesterRequestWithTimeout(CanReqId=0x7E0, CanReqData=[0x02, 0x01, PID])

        if RespMsg is not None:
            RespData = list(RespMsg.data)

            #print(RespData)

            #Update labels as per PID selection
            for i in range(0, 0x20):
                #print("i = %d" % i)
                PID = PID + 1

                BitValue = RespData[(int(i/8)+3)]
                #print(hex(BitValue))

                #Check if PID is supported and set status
                CBHandle = self.CB_SuppPIDList[i]
                CBHandle.setText("$" + str(hex(PID)).upper()[2:])
                if (BitValue & (0x80>>(i%8)))!=0x00:
                    CBHandle.setChecked(True)
                else:
                    CBHandle.setChecked(False)
        else:
            self.statusbar.showMessage("Unable to get PID support data", self.MSG_DISPLAY_TIME)

    def ProcessMode_01(self):
        P2_TIME_MS = 5

    # PID configuration: { PID: (Raw QLineEdit name, Physical QLineEdit name, num_bytes, offset, factor) }
        pid_config = {
            0x04: ("lineEdit_RawVal_PID_04", "lineEdit_PhyVal_PID_04", 1, 0, 2.55),
            0x05: ("lineEdit_RawVal_PID_05", "lineEdit_PhyVal_PID_05", 1, -40, 1),
            0x0C: ("lineEdit_RawVal_PID_0C", "lineEdit_PhyVal_PID_0C", 2, 0, 4),  # RPM = ((A*256)+B)/4
            0x22: ("lineEdit_RawVal_PID_22", "lineEdit_PhyVal_PID_22", 2, 0, 12.65),
            0x2C: ("lineEdit_RawVal_PID_2C", "lineEdit_PhyVal_PID_2C", 1, 0, 2.55),  # example
            0x31: ("lineEdit_RawVal_PID_31", "lineEdit_PhyVal_PID_31", 2, 0, 1),
        }

        for pid, (raw_name, phy_name, num_bytes, offset, factor) in pid_config.items():
        # Send Mode 01 request
            RespMsg = self.TesterRequestWithTimeout(CanReqId=0x7E0, CanReqData=[0x02, 0x01, pid], TOVal_ms=P2_TIME_MS)

            Raw_Value = "N/A"
            Physical_Value = "No Data"

            if RespMsg is not None:
                CanData = list(RespMsg.data)

                if num_bytes == 1:
                    Raw_Value = CanData[3]
                elif num_bytes == 2:
                    Raw_Value = CanData[3] * 256 + CanData[4]

                try:
                    Physical_Value = (Raw_Value + offset) / factor
                    Physical_Value = f"{Physical_Value:.2f}"
                except ZeroDivisionError:
                    Physical_Value = "Invalid Factor"

                Raw_Value = hex(Raw_Value)

        # Find the raw and physical line edits
            raw_edit = self.findChild(QtWidgets.QLineEdit, raw_name)
            phy_edit = self.findChild(QtWidgets.QLineEdit, phy_name)

            if raw_edit:
                raw_edit.setText(str(Raw_Value))
            if phy_edit:
                phy_edit.setText(str(Physical_Value))

        return
                
    def ProcessMode_03(self):
        P2_TIME_MS = 5
        dtc_description = {
            "P0100": "Mass or Volume Air Flow Circuit Malfunction",
            "P0101": "Mass or Volume Air Flow Circuit Range/Performance Problem",
            "P0102": "Mass or Volume Air Flow Circuit Low Input",
            "P0103": "Mass or Volume Air Flow Circuit High Input",
            "P0104": "Mass or Volume Air Flow Circuit Intermittent",
            "P0105": "Manifold Absolute Pressure/Barometric Pressure Circuit Malfunction",
            "P0106": "Manifold Absolute Pressure/Barometric Pressure Circuit Range/Performance Problem",
            "P0107": "Manifold Absolute Pressure/Barometric Pressure Circuit Low Input",
            "P0108": "Manifold Absolute Pressure/Barometric Pressure Circuit High Input",
            "P0109": "Manifold Absolute Pressure/Barometric Pressure Circuit Intermittent",
            "P0111": "Intake Air Temperature Circuit Malfunction",
            "P0112": "Intake Air Temperature Circuit Low Input"
        }
        
        self.table = self.findChild(QtWidgets.QTableWidget, "DTCList")
    
        
        RxCanMsg = self.TesterRequestWithTimeout(CanReqId=0x7DF, CanReqData=[0x01,0x03], TOVal_ms=P2_TIME_MS)
        
        num_dtcs = RxCanMsg.data[2]  # No of DTCs in the frame
        
    
        for i in range(num_dtcs):
            high_byte = RxCanMsg.data[3 + 2*i]  # Get the high byte of the DTC
            low_byte = RxCanMsg.data[4 + 2*i]   # Get the low byte of the DTC

        
            category_code = (high_byte & 0xC0) >> 6 #Getting the categoryof the DTC
        
            if category_code == 0b00:
                category = 'P'
            elif category_code == 0b01:
                category = 'C'
            elif category_code == 0b10:
                category = 'B'
            else:
                category = 'U'

            dtc_bytes = ((high_byte & 0x3F) << 8) | low_byte #Merge high byte and low byte
            dtcs = f"{category}{dtc_bytes:04X}"     #Add the category to the string
    
            description = dtc_description.get(dtcs, "Unknown DTC") #Get the description of the DTCs

            self.DTCList.setMinimumWidth(1000)
            self.DTCList.setItem(i, 0, QtWidgets.QTableWidgetItem(dtcs))
            self.DTCList.setItem(i, 1, QtWidgets.QTableWidgetItem(description))
            self.DTCList.resizeRowsToContents()
        return
        
        
    def ProcessMode_09(self):
        P2_TIME_MS = 5

    # PID → Description
        pid_description = {
            0x01: "VIN Message Count",
            0x02: "Vehicle Identification Number (VIN)",
            0x04: "Calibration ID"
        }

    # Map for setting values in lineEdits
        raw_value_widgets = {
            0x01: self.findChild(QtWidgets.QLineEdit, "lineEdit_RawVal_PID_01"),
            0x02: self.findChild(QtWidgets.QLineEdit, "lineEdit_RawVal_PID_02"),
            0x04: self.findChild(QtWidgets.QLineEdit, "lineEdit_RawVal_PID_5"),  # Rename to lineEdit_RawVal_PID_04 for consistency
        }

        physical_value_widgets = {
            0x01: self.findChild(QtWidgets.QLineEdit, "lineEdit_Val_PID_01"),
            0x02: self.findChild(QtWidgets.QLineEdit, "lineEdit_Val_PID_02"),
            0x04: self.findChild(QtWidgets.QLineEdit, "lineEdit_Val_PID_04"),
        }

        for PID in [0x01, 0x02, 0x04]:
            RespMsg = self.TesterRequestWithTimeout(CanReqId=0x7E0, CanReqData=[0x02, 0x09, PID], TOVal_ms=P2_TIME_MS)

            if RespMsg is not None:
                CanData = list(RespMsg.data)

                if PID == 0x01:
                    Raw_Value = str(CanData[3])
                    Physical_Value = str(CanData[3])  # VIN message count

                elif PID == 0x02:
                    vin_bytes = CanData[3:]
                    vin_string = ''.join(chr(b) for b in vin_bytes if b != 0x00)
                    Raw_Value = ' '.join(hex(b) for b in vin_bytes)
                    Physical_Value = vin_string

                elif PID == 0x04:
                    calid_bytes = CanData[3:]
                    calid_string = ''.join(chr(b) for b in calid_bytes if b != 0x00)
                    Raw_Value = ' '.join(hex(b) for b in calid_bytes)
                    Physical_Value = calid_string
                else:
                    Raw_Value = "N/A"
                    Physical_Value = "Unsupported PID"
            else:
                Raw_Value = "No Response"
                Physical_Value = "No Data"

        # Set text in line edits
            if raw_value_widgets[PID]:
                raw_value_widgets[PID].setText(Raw_Value)
            if physical_value_widgets[PID]:
                physical_value_widgets[PID].setText(Physical_Value)

        return


    def GetSettings(self):
        try:
            with open(self.SETTINGS_FILE) as f:
                self.JsonData = json.load(f)
        except:
            print("[SCAN TOOL][E] Unable to open json file")

    def On_General_Send_Btn_Click(self):
        if self.ConnectStatus==True:
            ReqId = int(self.lineEdit_ReqId.text(), 16)
            Data  = self.lineEdit_ReqData.text().split(' ')
            ReqBytes = []
            for value in Data:
                ReqBytes.append(int(value, 16))

            #Clear previous response
            self.lineEdit_RespId.setText("              ")
            self.lineEdit_RespData.setText("              ")

            #print("ReqId = %x Data = %s" % (ReqId, ReqBytes))
            RespMsg = self.TesterRequestWithTimeout(CanReqId=ReqId, CanReqData=ReqBytes)

            #print(RespMsg)

            if RespMsg is not None:
                if RespMsg.arbitration_id==0x7E8:
                    self.lineEdit_RespId.setText(str(hex(RespMsg.arbitration_id)))

                    RespData = list(RespMsg.data)
                    #print(RespData)
                    RespDataStr = ""
                    for Byte in RespData:
                        RespDataStr += format(Byte, '02x') + " "
                    self.lineEdit_RespData.setText(RespDataStr)
                else:
                    self.lineEdit_RespId.setText("no response")
                    self.lineEdit_RespData.setText("no response")
        else:
            self.statusbar.showMessage("CAN LOGGER - Not connected", self.MSG_DISPLAY_TIME)

    def TesterRequestWithTimeout(self, CanReqId=0x7E0, CanReqData=[0x00], TOVal_ms=P2_TIME_MS):
        if self.ConnectStatus==True:
            ReqMsg = self.CanHandle.CreateMessage(CanId=CanReqId, CanData=CanReqData)
            if self.CanHandle.SendCanMsg(ReqMsg)==False:
                self.statusbar.showMessage("CAN LOGGER - Unable to transmit", self.MSG_DISPLAY_TIME)
            Counter = TOVal_ms

            #Wait for proper response until timeout
            RespMsg = None
            while(Counter>0):
                #print(Counter)
                self.statusbar.showMessage("Waiting for response", self.MSG_DISPLAY_TIME)
                RespMsg = self.CanHandle.GetCanMsg(RespMsg)
                if RespMsg is not None:
                    if RespMsg.arbitration_id==0x7E8:
                        #print("OBD Resp received")
                        break
                Counter = Counter-1

            return(RespMsg)

    def Connect(self):
        self.GetSettings()

        logger_selected = self.JsonData['selected_can_logger']
        #print(logger_selected)

        logger_name = logger_selected['logger']

        if logger_name=="KORLAN":
            self.ConnectKorlan(logger_selected['baud_rate'])
        elif logger_name=="WAVESHARE_A":
            self.ConnectWaveshare_A(logger_selected['baud_rate'])

    def Disconnect(self):
        if self.ConnectStatus==True:
            self.ConnectStatus = False
            self.statusbar.showMessage("CAN LOGGER - Disconnected", self.MSG_DISPLAY_TIME)

    def ConnectKorlan(self, BaudRate):
        if self.ConnectStatus==False:
            try:
                self.CanHandle = korlan.CanTransceiver(baudrate=BaudRate)
                self.ConnectStatus = True
            except:
                self.statusbar.showMessage("KORLAN - Unable to open", self.MSG_DISPLAY_TIME)
            if self.ConnectStatus == True:
                self.statusbar.showMessage("KORLAN - Connected", self.MSG_DISPLAY_TIME)
        else:
            self.statusbar.showMessage("KORLAN - Already connected", self.MSG_DISPLAY_TIME)

    def ConnectWaveshare_A(self, BaudRate):
        if self.ConnectStatus==False:
            try:
                ConnPort = self.JsonData['selected_can_logger']['com_port']
                self.CanHandle = waveshare_a.CanTransceiver(ComPort=ConnPort, SerialBaudRate=115200)
                self.ConnectStatus = True
            except:
                self.statusbar.showMessage("WAVESHARE - Unable to open", self.MSG_DISPLAY_TIME)

            if self.ConnectStatus==True:
                self.statusbar.showMessage("WAVESHARE - Connected", self.MSG_DISPLAY_TIME)
        else:
            self.statusbar.showMessage("WAVESHARE - Already connected", self.MSG_DISPLAY_TIME)

    def Exit(self):
        exit(0)

    def About(self):
        QMessageBox.about(
            self,
            "Generic Scan Tool",
            "<p>Tool to access vehicle diagnostic data</p>",
        )

class Settings(QDialog, Ui_Settings):

    def __init__(self, SettingsFile, parent=None):
        super().__init__(parent)
        self.setupUi(self)
        self.connectSignalsSlots()

        self.SettingsFile = SettingsFile
        #print(self.SettingsFile)

        self.GetSettings()
        self.NewLoggerSelected()
        #print(self.JsonData)

    def connectSignalsSlots(self):
        self.Btn_Ok.clicked.connect(self.OkClicked)
        self.pushButton_Refresh.clicked.connect(self.PopulateComPorts)
       # self.pushButton_Refresh.setEnabled(False)
        self.comboBox_Logger.currentTextChanged.connect(self.NewLoggerSelected)

    def GetSerialPortsList(self):
        Ports = ['COM%s' % (i + 1) for i in range(256)]

        PortList = []
        for Port in Ports:
            try:
                s = serial.Serial(Port)
                s.close()
                PortList.append(Port)
            except (OSError, serial.SerialException):
                pass

        #print(PortList)
        return(PortList)

    def NewLoggerSelected(self):
        logger_selected = self.comboBox_Logger.currentText()
        all_loggers     = self.JsonData['supported_can_loggers']

        #Enable the baudrate combobox for the supported logger
        if logger_selected=="WAVESHARE_A":
            self.comboBox_ComPort.setEnabled(True)
      #      self.pushButton_Refresh.setEnabled(True)
            self.PopulateComPorts()
        else:
            self.comboBox_ComPort.setEnabled(False)
         #   self.pushButton_Refresh.setEnabled(False)

        for logger in all_loggers:
           if logger['logger']==logger_selected:
               break

        #Enable/Disable CAN channel if supported for selected logger
        supported_can_channels = logger['channels']
        if 'can1' in supported_can_channels:
            self.checkBox_CAN1.setEnabled(True)
        else:
            self.checkBox_CAN1.setEnabled(False)

        if 'can2' in supported_can_channels:
            self.checkBox_CAN2.setEnabled(True)
        else:
            self.checkBox_CAN2.setEnabled(False)

    def PopulateComPorts(self):
        ComPortsList = self.GetSerialPortsList()

        self.comboBox_ComPort.clear()
        for ComPort in ComPortsList:
            self.comboBox_ComPort.addItem(ComPort)

    def GetSettings(self):
        try:
            with open(self.SettingsFile) as f:
                self.JsonData = json.load(f)

            #set the parameters in the dialog as per json file
            #self.comboBox_Logger.text(self.JsonData['selected_can_logger']['logger'])
            #self.comboBox_BaudRate.text(str(self.JsonData['selected_can_logger']['baud_rate']))
        except:
            print("[SETTINGS][E] Unable to open json file")

    def OkClicked(self):
        self.JsonData['selected_can_logger']['logger'] = self.comboBox_Logger.currentText()
        self.JsonData['selected_can_logger']['com_port'] = self.comboBox_ComPort.currentText()
        self.JsonData['selected_can_logger']['baud_rate'] = int(self.comboBox_BaudRate.currentText())
        if self.checkBox_CAN1.isChecked() and self.checkBox_CAN2.isChecked():
            self.JsonData['selected_can_logger']['channels'] = "can1,can2"
        elif self.checkBox_CAN1.isChecked():
            self.JsonData['selected_can_logger']['channels'] = "can1"
        elif self.checkBox_CAN2.isChecked():
            self.JsonData['selected_can_logger']['channels'] = "can2"
        else:
            self.JsonData['selected_can_logger']['channels'] = "can1"

        #print(self.JsonData)

        try:
            with open(self.SettingsFile, 'w', encoding='utf-8') as f:
                json.dump(self.JsonData, f, indent=4)
            print("[SCAN TOOL][I] Settings written to file")
        except:
            print("[SCAN TOOL][E] JSON DATA - Unable to write to file")
			
def main():
    app = QApplication(sys.argv)
    win = Window()
    win.show()
    sys.exit(app.exec())

if __name__ == "__main__":
    main()
