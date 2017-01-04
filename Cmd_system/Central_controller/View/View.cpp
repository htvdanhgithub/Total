#include "..\Utils\Logger.h"
#include "View.h"

View::View(void)
{
}
View::~View(void)
{
}
void View::Initiate()
{
	Serial.begin(9600);	
}
void View::GSMConnect() 
{
	LOG(V_DEBUG, "SMS Messages Receiver\r\n");
	// connection state
	boolean notConnected = true;

	// Start GSM connection
	while (notConnected) 
	{
		if (m_GsmAccess.begin(PINNUMBER) == GSM_READY) 
		{
			notConnected = false;
		} 
		else 
		{
			LOG(V_DEBUG, "Not connected\r\n");
			delay(1000);
		}
	}

	LOG(V_DEBUG, "GSM initialized\r\n");
	LOG(V_DEBUG, "Waiting for messages\r\n");
}
boolean View::SMSAvailable() 
{
	return m_Sms.available();
}
void View::SMSGetRemoteNumber(char *senderNumber, uint8_t len) 
{
	m_Sms.remoteNumber(senderNumber, len);
}
int View::SMSGetMsg(char* result, int size)
{
	PinHigh(PIN_SMS_RECV);
	
	char c;
	int i = 0;
    while (c = m_Sms.read()) 
	{
		if(i < size - 1)
		{
			result[i++] = c;
		}
    }

	result[i] = 0;
	LOG(V_DEBUG, "i: %d\r\n", i);
	LOG(V_DEBUG, "Receive Msg: %s\r\n", result);
	
	PinLow(PIN_SMS_RECV);
	return i;
}
int View::ReadSerial(char* result, int size)
{
	int i = 0;
	while (1)
	{
		while (Serial.available() > 0)
		{
			char inChar = Serial.read();
			if (inChar == '\n')
			{
				result[i] = '\0';
				Serial.flush();
				LOG(V_DEBUG, "Msg recv: %s\r\n", result);
				return 0;
			}
			if (inChar != '\r')
			{
				if(i < size - 1)
				{
					result[i++] = inChar;
				}
				else
				{
					result[i] = '\0';
				}
			}
		}
	}
}

void View::SMSFlush() 
{
	m_Sms.flush();
}
void View::SMSSend(const char * remoteNum, const char *txtMsg)
{
	PinHigh(PIN_SMS_SEND);
	
	LOG(V_DEBUG, "Msg: %s\r\n", txtMsg);
	LOG(V_DEBUG, "Sent to %s\r\n", remoteNum);
#if !(UNITTEST)
	m_Sms.beginSMS(remoteNum);
	m_Sms.print(txtMsg);
	m_Sms.endSMS();	
#endif	
	PinLow(PIN_SMS_SEND);
}
void View::PinMode(uint8_t pin, uint8_t mode)
{
	LOG(V_DEBUG, "INFO: PinMode (%d, %d)\r\n", pin, mode);	
	pinMode(pin, mode);
}
void View::PinArrayMode(uint8_t pin_from, uint8_t pin_to, uint8_t mode)
{
	for(uint8_t i = pin_from; i <= pin_to; i++)
	{
		PinMode(i, mode);
	}
}
void View::PinSet(uint8_t pin, uint8_t value)
{
	LOG(V_DEBUG, "INFO: PinSet (%d, %d)\r\n", pin, value);	
	digitalWrite(pin, value);
}
uint8_t View::PinGet(uint8_t pin)
{
	return digitalRead(pin);
}
void View::PinHigh(uint8_t pin)
{
	PinSet(pin, HIGH);
}
void View::PinLow(uint8_t pin)
{
	PinSet(pin, LOW);
}
void View::PinArraySet(uint8_t pin_from, uint8_t pin_to, uint8_t value)
{
	for(uint8_t i = pin_from; i <= pin_to; i++)
	{
		PinSet(i, value);
	}
}
void View::PinArrayHigh(uint8_t pin_from, uint8_t pin_to)
{
	PinArraySet(pin_from, pin_to, HIGH);
}
void View::PinArrayLow(uint8_t pin_from, uint8_t pin_to)
{
	PinArraySet(pin_from, pin_to, LOW);
}
void View::EEPROMWrite(const char* data, uint8_t start, uint8_t len)
{
	for(uint8_t i = 0; i < len; i++)
	{
		EEPROM.write(start + i, data[i]);
	}
}
void View::EEPROMRead(char* data, uint8_t start, uint8_t len)
{
	for(uint8_t i = 0; i < len; i++)
	{
		data[i] = EEPROM.read(start + i);
	}
}
