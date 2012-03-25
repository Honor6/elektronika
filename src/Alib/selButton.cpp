/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include						"export.h"
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	SELBUTTON.CPP				(c)	YoY'04						WEB: www.aestesis.org
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include						<stdio.h>
#include						"selButton.h"
#include						"interface.h"
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

ADLL ACI						AselButton::CI=ACI("AselButton", GUID(0xAE57E515,0x00001140), &Aobject::CI, 0, NULL);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

ADLL AselButton::AselButton(char *name, Aobject *L, int x, int y, int nx, int ny, Aresobj *o, int ow, int oh, char *text) : Aobject(name, L, x, y, 4, 4)
{
	bmp=new Abitmap(o);
	this->ow=ow;
	this->oh=oh;
	this->nx=nx;
	this->ny=ny;
	size(nx*(ow+2)-2, ny*(oh+2)-2);
	over=-1;
	this->text=null;
	if(text)
		this->text=strdup(text);
	set(0);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

ADLL AselButton::AselButton(char *name, Aobject *L, int x, int y, int nx, int ny, Abitmap *b, int ow, int oh, char *text) : Aobject(name, L, x, y, 4, 4)
{
	bmp=new Abitmap(b->w, b->h);
	bmp->set(0, 0, b, bitmapDEFAULT, bitmapDEFAULT);
	this->ow=ow;
	this->oh=oh;
	this->nx=nx;
	this->ny=ny;
	size(nx*(ow+2)-2, ny*(oh+2)-2);
	over=-1;
	set(0);
	this->text=null;
	if(text)
		this->text=strdup(text);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

ADLL AselButton::~AselButton()
{
	if(bmp)
		delete(bmp);
	if(text)
		free(text);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

ADLL bool AselButton::mouse(int x, int y, int state, int event)
{
	switch(event)
	{
		case mouseLDOWN:
		mouseCapture(true);
		{
			int vx=x/(ow+2);
			int	vy=y/(oh+2);
			int	n=vy*nx+vx;
			if(n!=over)
			{
				over=n;
				repaint();
			}
		}
		return true;

		case mouseNORMAL:
		cursor(cursorHANDSEL);
		focus(this);
		if(!(state&mouseL))
		{
			int vx=x/(ow+2);
			int	vy=y/(oh+2);
			int	n=vy*nx+vx;
			if(n!=over)
			{
				over=n;
				repaint();
			}
		}
		return true;

		case mouseLUP:
		mouseCapture(false);
		if(press!=over)
		{
			press=over;
			father->notify(this, nyCHANGE, press);
			repaint();
		}
		return TRUE;

		case mouseLEAVE:
		over=-1;
		repaint();
		return true;
	}
	return FALSE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

ADLL void AselButton::change(Abitmap *b)
{
	bmp->set(0, 0, b, bitmapDEFAULT, bitmapDEFAULT);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

ADLL void AselButton::change(int nx, int ny)
{
	this->nx=nx;
	this->ny=ny;
	size(nx*(ow+2)-2, ny*(oh+2)-2);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

ADLL void AselButton::set(int n)
{
	press=n%(nx*ny);
	repaint();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

ADLL int AselButton::get()
{
	return press;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

ADLL void AselButton::paint(Abitmap *bitmap)
{
	char	tt[1024];
	if(text)
		strcpy(tt, text);
	char	*s=tt;
	if(bmp)
	{
		int	n=0;
		int	i,j;
		int	max=bmp->h/oh;
		for(j=0; j<ny; j++)
		{
			for(i=0; i<nx; i++)
			{
				int	nn=(press==n)?2:((over==n)?1:0);

				if(text)
				{
					Afont	*f=alib.getFont(fontTERMINAL06);
					int		x=((i+1)*(ow+2)-2)-ow;
					int		y=((j+1)*(oh+2)-2)-oh;
					bitmap->set(x, y, nn*ow, 0, ow, oh, bmp, bitmapDEFAULT, bitmapDEFAULT);
					if(*s)
					{
						char	*str=s;
						while(*s&&(*s!=','))
							s++;
						if(*str)
						{
							*(s++)=0;
							Arectangle r=f->getRectangle(0, 0, str);
							f->set(bitmap, 1+x+(ow-r.w)/2, 1+y+(oh-r.h)/2, str, 0xff000000); 
						}
					}
					n++;
				}
				else
				{
					bitmap->set(((i+1)*(ow+2)-2)-ow, ((j+1)*(oh+2)-2)-oh, nn*ow, n*oh, ow, oh, bmp, bitmapDEFAULT, bitmapDEFAULT);
					n++;
					if(n>=max)
						return;
				}
			}
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////