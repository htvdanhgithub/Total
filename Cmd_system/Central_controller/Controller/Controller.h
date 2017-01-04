#ifndef CONTROLLER_H
#define CONTROLLER_H

#define C_DEBUG true

#include "..\Common\Common.h"
#include "..\View\View.h"
#include "..\Model\Model.h"

typedef struct
{
	char  master_number[MAX_PHONE_LEN];
	uint8_t  sw1_status;
} ROM_t;
class Controller
{
	// Operations
	public:
		void Initiate(void);
		void Execute();
		
		Controller();   // This is the constructor declaration
		~Controller();  // This is the destructor: declaration	
	protected:
		void WaitAndProcessMsg();
		boolean HandleMsg(const char* senderNumber, const char* msg);
		int8_t GetSwPin(uint8_t pin);
		void ReportToMaster(const char* senderNumber, const char* msg, boolean forced = false);
	// Attributes
	protected:
		Model m_Model;
		View  m_View;
		char  m_SMSSend[MAX_MSG_LEN];
		char  m_SMSRecv[MAX_MSG_LEN];
		ROM_t m_RomInf;
};

#endif // CONTROLLER_H
