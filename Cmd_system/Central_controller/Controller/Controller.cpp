#include "..\Utils\Logger.h"
#include "Controller.h"

#define START_MARK "<<<<"
#define END_MARK ">>>>"

Controller::Controller(void)
{
	m_RomInf.master_number[0] = 0;
}
Controller::~Controller(void)
{
}

void Controller::Initiate(void)
{
	m_View.Initiate();
	
	LOG(C_DEBUG, "<<<<Start...>>>>\r\n");
	m_View.EEPROMRead((char*)&m_RomInf, 0, MAX_PHONE_LEN + 1);
	LOG(C_DEBUG, "Report num: %s\r\n", m_RomInf.master_number);
	LOG(C_DEBUG, "Sw1 status: %d\r\n", m_RomInf.sw1_status);
	
	m_View.PinMode(PIN_ARDUINO_STARTING, OUTPUT);
	m_View.PinMode(PIN_GSM_CONNECTED, OUTPUT);
	m_View.PinMode(PIN_SWITCH1, OUTPUT);
	m_View.PinMode(PIN_MANUAL_BTN, INPUT);
	
	m_View.PinArraySet(PIN_OUT_START, PIN_OUT_END, LOW);
#if !(UNITTEST)
	m_View.GSMConnect();
	ReportToMaster("Device", "<<<<Start...>>>>", true);
#endif	
	m_View.PinHigh(PIN_GSM_CONNECTED);
	
	m_View.PinSet(PIN_SWITCH1, m_RomInf.sw1_status);

}
int8_t Controller::GetSwPin(uint8_t pin)
{
	switch(pin)
	{
		case 1:
			return PIN_SWITCH1;
			break;
		case 2:
			return PIN_SWITCH2;
			break;
		case 3:
			return PIN_SWITCH3;
			break;
		case 4:
			return PIN_SWITCH4;
			break;
		default:
			return -1;
			break;
	}
}
void Controller::ReportToMaster(const char* senderNumber, const char* m_SMSRecv, boolean forced)
{
	char sSMSSend[MAX_MSG_LEN + MAX_PHONE_LEN];
	if((m_RomInf.master_number[0] != 0) && ((forced == true) || (strcmp(senderNumber, m_RomInf.master_number) != 0)))
	{
		sprintf(sSMSSend, "%s: %s\r\n", senderNumber, m_SMSRecv);
    	m_View.SMSSend(m_RomInf.master_number, sSMSSend);
	}
	
}
boolean Controller::HandleMsg(const char* senderNumber, const char* m_SMSRecv)
{
	boolean ret = true;
	uint8_t len;
	uint8_t on = HIGH;
	int8_t pin = 1;
	uint8_t port;
	
	if(m_SMSRecv[0] != '#')
	{
		goto __wrong_format;
	}

	switch(m_SMSRecv[1])
	{
		case 'M':
			if(strlen(m_SMSRecv) > 3)
			{
				goto __wrong_format;
			}
			on = true;
		break;
		case 'T':
			if(strlen(m_SMSRecv) > 3)
			{
				goto __wrong_format;
			}
			on = LOW;
		break;
		case 'R':
			len = strlen(m_SMSRecv + 2);
			if(len == 0)
			{
				memset(m_RomInf.master_number, 0, MAX_PHONE_LEN);
			}
			else
			{
				if((len < 10) || (len > 15) || (!m_Model.IsStringDigit(m_SMSRecv + 2)))
				{
					goto __wrong_format;
				}
				sprintf(m_RomInf.master_number, "+84%s", m_SMSRecv + 3);
			}
			m_View.EEPROMWrite((char *)&m_RomInf, 0, MAX_PHONE_LEN + 1);

			LOG(C_DEBUG, "Master: %s\r\n", m_RomInf.master_number);
			sprintf(m_SMSSend, "Report num %s\r\n", m_RomInf.master_number);
			goto __exit;
		break;
		default:
			goto __wrong_format;
		break;
	}

//	if((!isdigit(m_SMSRecv[2])) || (m_SMSRecv[2] < '1') || (m_SMSRecv[2] > '4'))
	if((!isdigit(m_SMSRecv[2])) || (m_SMSRecv[2] != '1'))
	{
		goto __wrong_format;
	}
//	port = m_SMSRecv[2] - '0';
//	pin = GetSwPin(port);
	
	sprintf(m_SMSSend, "%d duoc %s\r\n", port, (on == HIGH) ? "MO" : "TAT");
	m_RomInf.sw1_status = on;
	
	m_View.EEPROMWrite((char *)&m_RomInf, 0, MAX_PHONE_LEN + 1);
	
	m_View.PinSet(PIN_SWITCH1, m_RomInf.sw1_status);
	goto __exit;
	
__wrong_format:
	LOG(C_DEBUG, "Wrong format\r\n");

	strcpy(m_SMSSend, "Yeu cau khong hop le.\r\n");
	ret = false;
__exit:
		
	LOG(C_DEBUG, "Exit\r\n");

	m_View.SMSSend(senderNumber, m_SMSSend);

	ReportToMaster(senderNumber, m_SMSRecv);
	return ret;
}
void Controller::WaitAndProcessMsg()
{
	char c;
	char senderNumber[MAX_PHONE_LEN];
#if !(UNITTEST)	
	// If there are any SMSs available()
	if (m_View.SMSAvailable()) 
	{
		// Get remote number
		m_View.SMSGetRemoteNumber(senderNumber, MAX_PHONE_LEN);
		LOG(C_DEBUG, "Recv from: %s\r\n", senderNumber);

		m_View.SMSGetMsg(m_SMSRecv, MAX_MSG_LEN);
		
		LOG(C_DEBUG, "END OF MESSAGE\r\n");

		// Delete message from modem memory
		m_View.SMSFlush();
		
		LOG(C_DEBUG, "MESSAGE DELETED\r\n");

		HandleMsg(senderNumber, m_SMSRecv);
	}
#else
		m_View.PinHigh(PIN_SMS_RECV);
		// Get remote number
		strcpy(senderNumber, "+84907710730");
		LOG(C_DEBUG, "Recv from: %s\r\n", senderNumber);
		m_View.ReadSerial(m_SMSRecv, MAX_MSG_LEN);
		LOG(C_DEBUG, "END OF MESSAGE\r\n");

		LOG(C_DEBUG, "MESSAGE DELETED\r\n");

		m_View.PinLow(PIN_SMS_RECV);
		HandleMsg(senderNumber, m_SMSRecv);
#endif	
}

void Controller::Execute()
{
	if(m_View.PinGet(PIN_MANUAL_BTN) == LOW)
	{
		if (m_RomInf.sw1_status == HIGH)
		{
			m_RomInf.sw1_status = LOW;
		}
		else
		{
			m_RomInf.sw1_status = HIGH;
		}
		m_View.EEPROMWrite((char *)&m_RomInf, 0, MAX_PHONE_LEN + 1);
		
		m_View.PinSet(PIN_SWITCH1, m_RomInf.sw1_status);
	}
	WaitAndProcessMsg();
	delay(1000);
	
}
