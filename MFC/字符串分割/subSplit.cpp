		char *p;
		const char *d = " ,*";
		p = strtok(str.GetBuffer(), d);
		while(p)
		{
			vShort.push_back(atoi(p));
			p=strtok(NULL,d);
		}