 fread(   void   *buffer,   size_t   size,   size_t   count,   FILE   *stream   ) 
 // buffer   是读取的数据存放的内存的指针（可以是数组，也可以是新开辟的空间，buffer就是一个索引）   
  //  size       是每次读取的字节数  
 // count     是读取次数  
 // strean   是要读取的文件的指针 
  
FILE *fin,*out;
in=fopen("input.bin","rb");
out=fopen("output.bin","wb");
	
//读取int
fread(&n,4,1,in);

//读取长度为n的int数组a[]
fread(a+1,4,n,fin);

//输出int
fwrite(&n,4,1,out);

//输出数组
fwrite(a+1,4,n,out);

	
