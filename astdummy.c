void checkGlobal(char* name,int line_num){
	int pos=hashFunc(name);
	int i=1;
	while(gST[pos].s!=empty)
	{
		if(i==5){
			return;
		}
		if(!strcmp(gST[pos].value,name))
		{
			printf("ERROR line %d:Variable %s already declared as a global can't be declared again\n",line_num,name);
			return;
			//exit(1);
		}
		pos = (pos + i*i)%M_SIZE;
		i++;
	}
}
