//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "U1.h"
#include <stdio.h>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
FILE *F;
AnsiString SName = "����������";
short damp[10000000];
#define SIZE_OF_FILE 100000
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button4Click(TObject *Sender)
{

unsigned i,ii;

if (SaveDialog1->Execute())
     {
     SName = SaveDialog1->FileName;
     if ((F = fopen(SName.c_str(), "wb")) == NULL)
          {
          ShowMessage("���� �� ������� �������");
          return;
          }
 /*   //���� � �������� � 256      ���� 00000006
      for(i=0;i<20000;i++)
      	{
          for(ii=0;ii<256;ii++)
      		{
               damp[(i*256)+ii]=(ii*4)-512;
               }
          }
 */
 /*
   //������� �������      ���� 00000007
      for(i=0;i<20000;i++)
      	{
          for(ii=0;ii<256;ii++)
      		{
               damp[(i*256)+ii]=500;
               }
          }
 */

 /*  //������ �������      ���� 00000008
      for(i=0;i<20000;i++)
      	{
          for(ii=0;ii<256;ii++)
      		{
               damp[(i*256)+ii]=-500;
               }
          } */

/*   //���� � �������� � 1024      ���� 00000009
   for(i=0;i<2000;i++)
     	{
          for(ii=0;ii<1024;ii++)
      		{
               damp[(i*1024)+ii]=ii-512;
               }
          }


   //���� � �������
   for(i=0;i<256;i++)
     	{
        damp[i]=0xffff;
        }
     damp[0]=1234; */


  /*     //���� � �������� � 128      ���� 00000009
   for(i=0;i<2000;i++)
     	{
          for(ii=0;ii<128;ii++)
      		{
               damp[(i*128)+ii]=ii*4+300;
               }
          } */

                 //���� � �������� � 256      ���� 00000009
 /*  for(i=0;i<2000;i++)
     	{
          for(ii=0;ii<256;ii++)
      		{
               damp[(i*256)+ii]=ii*2+300;
               }
          }  */

        for(i=0;i<1000;i++)
     	{
          for(ii=0;ii<512;ii++)
      		{
               damp[(i*512)+ii]=ii+300;
               }
          }
     fwrite(damp,sizeof(char),SIZE_OF_FILE,F);           // ������ i
     fclose(F);


     }
}
//---------------------------------------------------------------------------
 