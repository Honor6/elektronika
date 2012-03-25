/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	BUGGER.H					(c)	YoY'02						WEB: www.aestesis.org
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef							_BUFFER_H_
#define							_BUFFER_H_
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include						"types.h"
#include						"file.h"
#include						"section.h"
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//	If you use directly the variables in the class API, it's at your own risks. Prefer the methods...   

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define							guidBUFFER						(Abuffer::CI.guid)

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//! memory file manager
class Abuffer : public Afile
{
public:
	ALIBOBJ

	ADLL						Abuffer							(char *name, int size);
	ADLL virtual				~Abuffer						();

	ADLL virtual int			peek							(void *p, int s);

	ADLL virtual int			read							(void *p, int s);
	ADLL virtual int			write							(void *p, int s);

	ADLL virtual bool			writeString						(char *s);
	ADLL virtual bool			readString						(char *s);
	ADLL virtual bool			readStringAlloc					(char **s);

	ADLL virtual bool			seek							(sqword n);
	ADLL virtual sqword			getSize							();

	ADLL virtual void			clear							();

	virtual bool				isOK							()						{ return true; }
	
	sqword						getFreeSpace					()						{ return bufsize-size; }

	// private

	int							bufsize;
	char						*buffer;
	Asection					section;
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#endif							//_BUFFER_H_
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////