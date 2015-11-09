#include "24c01.h"
#include "i2c.h"

//-----------------------------------------------
char _24c01_read_byte(short adr)
{
char temp;

return temp;
}


//-----------------------------------------------
void _24c01_write_2byte(short adr,short data)
{
i2c_Start();
i2c_SendByte(0xa0);
if(i2c_ReadAcknowledge()) goto Stop_label_24c01_write_2byte;
i2c_SendByte((char)adr);
if(i2c_ReadAcknowledge()) goto Stop_label_24c01_write_2byte;
i2c_SendByte(data);
i2c_ReadAcknowledge();
i2c_SendByte(data>>8);
i2c_ReadAcknowledge();
Stop_label_24c01_write_2byte: 
i2c_Stop();
}

//-----------------------------------------------
short _24c01_read_2byte(short adr)
{
short temp;
char temp1;
i2c_Start();
i2c_SendByte(0xa0);
if(i2c_ReadAcknowledge()) goto Stop_label_24c01_read_2byte;
i2c_SendByte((char)adr);
if(i2c_ReadAcknowledge()) goto Stop_label_24c01_read_2byte;
i2c_Restart();
i2c_SendByte(0xa1);
if(i2c_ReadAcknowledge()) goto Stop_label_24c01_read_2byte;
temp1=i2c_ReadByte();
i2c_SendAcknowledge(1);
temp=i2c_ReadByte();
i2c_SendAcknowledge(0);
Stop_label_24c01_read_2byte: 
i2c_Stop();
temp<<=8;
temp+=temp1;
return temp;
}

//-----------------------------------------------
void _24c01_read_nbyte(short adr, char* buff, char n)
{
char i;
i2c_Start();
i2c_SendByte(0xa0);
if(i2c_ReadAcknowledge()) goto Stop_label_24c01_read_nbyte;
i2c_SendByte((char)adr);
if(i2c_ReadAcknowledge()) goto Stop_label_24c01_read_nbyte;
i2c_Restart();
i2c_SendByte(0xa1);
if(i2c_ReadAcknowledge()) goto Stop_label_24c01_read_nbyte;
for(i=0;i<(n-1);i++)
	{
	buff[i]=i2c_ReadByte();
	i2c_SendAcknowledge(1);
	}
buff[i]=i2c_ReadByte();
i2c_SendAcknowledge(0);
Stop_label_24c01_read_nbyte: 
i2c_Stop();

}


/*----------------------------------------------------------------------------
 * end of file
 *---------------------------------------------------------------------------*/
