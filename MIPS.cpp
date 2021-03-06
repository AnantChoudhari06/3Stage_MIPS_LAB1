#include<iostream>
#include<string>
#include<vector>
#include<bitset>
#include<fstream>
#include<stdlib.h>
using namespace std;
#define ADDU 1
#define SUBU 3
#define AND 4
#define OR  5
#define NOR 7
#define MemSize 65536 // memory size, in reality, the memory size should be 2^32, but for this lab, for the space resaon, we keep it as this large number, but the memory is still 32-bit addressable.


class RF
{
    public:
        bitset<32> ReadData1, ReadData2; 
     	RF()
    	{ 
          Registers.resize(32);  
          Registers[0] = bitset<32> (0);  
        }
	
        void ReadWrite(bitset<5> RdReg1, bitset<5> RdReg2, bitset<5> WrtReg, bitset<32> WrtData, bitset<1> WrtEnable)
        {   
            // implement the funciton by you.                
         }
		 
	void OutputRF()
             {
               ofstream rfout;
                  rfout.open("RFresult.txt",std::ios_base::app);
                  if (rfout.is_open())
                  {
                    rfout<<"A state of RF:"<<endl;
                  for (int j = 0; j<32; j++)
                      {        
                        rfout << Registers[j]<<endl;
                      }
                     
                  }
                  else cout<<"Unable to open file";
                  rfout.close();
               
               }     
	private:
            vector<bitset<32> >Registers;
	
};

class ALU
{
      public:
             bitset<32> ALUresult;
             bitset<32> ALUOperation (bitset<3> ALUOP, bitset<32> oprand1, bitset<32> oprand2)
             {   
                 // implement the ALU operations by you. 
                 return ALUresult;
               }            
};

class INSMem
{
      public:
          bitset<32> Instruction;
          INSMem()
          {       IMem.resize(MemSize); 
                  ifstream imem;
                  string line;
                  int i=0;
                  imem.open("imem.txt");
                  if (imem.is_open())
                  {
                  while (getline(imem,line))
                     {      
                        IMem[i] = bitset<8>(line);
                        i++;
                     }
                     
                  }
                  else cout<<"Unable to open file";
                  imem.close();
                     
                  }
                  
          bitset<32> ReadMemory (bitset<32> ReadAddress) 
              {    
               // implement by you. (Read the byte at the ReadAddress and the following three byte).
              	Instruction = bitset<32>((IMem[ReadAddress.to_ulong()].to_ulong()) << 24 | (IMem[ReadAddress.to_ulong()+1].to_ulong()) << 16 | (IMem[ReadAddress.to_ulong()+2].to_ulong()) << 8 | (IMem[ReadAddress.to_ulong()+3].to_ulong()));
                return Instruction;



               return Instruction;     
              }     
      
      private:
           vector<bitset<8> > IMem;
      
};
      
class DataMem    
{
      public:
          bitset<32> readdata;  
          DataMem()
          {
             DMem.resize(MemSize); 
             ifstream dmem;
                  string line;
                  int i=0;
                  dmem.open("dmem.txt");
                  if (dmem.is_open())
                  {
                  while (getline(dmem,line))
                       {      
                        DMem[i] = bitset<8>(line);
                        i++;
                       }
                  }
                  else cout<<"Unable to open file";
                  dmem.close();
          
          }  
          bitset<32> MemoryAccess (bitset<32> Address, bitset<32> WriteData, bitset<1> readmem, bitset<1> writemem) 
          {    
               
               // implement by you.
               return readdata;     
          }   
                     
          void OutputDataMem()
          {
               ofstream dmemout;
                  dmemout.open("dmemresult.txt");
                  if (dmemout.is_open())
                  {
                  for (int j = 0; j< 1000; j++)
                       {     
                        dmemout << DMem[j]<<endl;
                       }
                     
                  }
                  else cout<<"Unable to open file";
                  dmemout.close();
               
               }             
      
      private:
           vector<bitset<8> > DMem;
      
};  

void dumpResults(bitset<32> pc, bitset<5> WrRFAdd, bitset<32> WrRFData, bitset<1> RFWrEn, bitset<32> WrMemAdd, bitset<32> WrMemData, bitset<1> WrMemEn)
{
                  ofstream fileout;
                  
                  fileout.open("Results.txt",std::ios_base::app);
                  if (fileout.is_open())
                  {
                  
                  fileout <<pc<<' '<<WrRFAdd<<' '<<WrRFData<<' '<<RFWrEn<<' '<<WrMemAdd<<' '<<WrMemData<<' '<<WrMemEn << endl;
                     
                  }
                  else cout<<"Unable to open file";
                  fileout.close();

}

   
int main()
 {   
     int progCounter=0;
     bitset<32> IF_Mem;
     bitset<32> ProgCounter4;



     
     RF myRF;
     ALU myALU;
     INSMem myInsMem;
     DataMem myDataMem;
     bitset<32> opcode;
    
     bitset<5> Rs;
     bitset<5> Rt;
     bitset<5> Rd;
     bitset<5> Function;
     bitset<17> extImm;
     bitset<26> immAddr; 
     bitset<32> decodInst;


   while (progCounter < 12) //each loop body corresponds to one clock cycle.
 	{
        
	   ProgCounter4 = bitset<32> (progCounter);

       



       IF_Mem = myInsMem.ReadMemory(progCounter);
       //cout<<"The instructtion is" << IF_Mem << "\n";
       
       bitset<32> decodInst(IF_Mem.to_string().substr(0,31));
       bitset<6> opcode(IF_Mem.to_string().substr(0,6));
       //cout << opcode ;
       
        
       if(opcode == 0x00)
       {
       	    

            bitset<5> Rs(IF_Mem.to_string().substr(6,5));
            bitset<5> Rt(IF_Mem.to_string().substr(11,5));
            bitset<5> Rd(IF_Mem.to_string().substr(16,5));
            bitset<6> Function(IF_Mem.to_string().substr(26,6));
            cout<< "Rs " << Rs << " Rt  "<< Rt << " Rd" << Rd << " Function "<< Function << "\n";
            
       }

       else if (opcode == 0x2 | opcode == 0x3F)
       {
            bitset<26> immAddr(IF_Mem.to_string().substr(6,26));
            cout<<"J type"<<"\n"; 
            if(opcode == 0x3F)
            {
            	cout<<"Halt Detected";
            	exit(1);
            }

       }

   		else
   		{
   			bitset<5> Rs(IF_Mem.to_string().substr(6,5));
            bitset<5> Rt(IF_Mem.to_string().substr(11,5));
            bitset<16> extImm(IF_Mem.to_string().substr(16,16));
            cout<< "Rs " << Rs << " Rt  "<< Rt<< " Immediate "<< extImm << "\n";

   		}


	   // At the end of each cycle, fill in the corresponding data into "dumpResults" function to output files.
//     // The first dumped pc value should be 0.	
//     dumpResults(pc, , , , , , );      
      

      
     
       progCounter = progCounter+4;
	   //cout << "PC is" << ProgCounter4 << "\n";  

    }
	
	
	
//  
//    }
      
// 	      myRF.OutputRF(); // dump RF; 
//           myDataMem.OutputDataMem(); // dump data mem
      
//           return 0;





        
   }




// if (OPCODE  ==  0b000000)
//         {
            
//         }
//         else if (OPCODE == 0b000010 | OPCODE == 0b111111)
//         {
//             cout << "J-TYPE" << "\n"; 
//             bitset<6> Rs = bitset<6>(conv_bit_to_string.substr(6,26));
        
//         }
//         else 
//         {
//             cout << "I-TYPE" << "\n"; 
//             bitset<6> Rs = bitset<6>(conv_bit_to_string.substr(6,5));
//             bitset<6> Rt = bitset<6>(conv_bit_to_string.substr(11,5));
//             bitset<6> Immediate = bitset<6>(conv_bit_to_string.substr(16,17));

//         }
