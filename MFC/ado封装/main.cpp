 	CString szFileName = "D:\\康如来\\中心端软件\\NormalEcg\\Bin\\StaticECG.mdb";	 
 	CString szCon = "Provider=Microsoft.Jet.OLEDB.4.0;Data Source=" + szFileName + ";";
	CString szQuery = "INSERT INTO data('name','del') VALUES('dsadsa', '1');";
	//szCon.Format("Provider=Microsoft.Jet.OLEDB.4.0;Data Source=%s\\StaticECG.mdb;Mode=ReadWrite;Persist Security Info=False",szFileName);

	CADODatabase staticEcgMdb;
	if(!staticEcgMdb.Open(szCon))
		return;

	CString szQuery1 = "select * from data;";

	CADORecordset rs(&staticEcgMdb);
	rs.Open(szQuery1);

	CString name, did;
	rs.GetFieldValue( "name", name);
	rs.GetFieldValue( "did", did);
	
	AfxMessageBox(name);
	AfxMessageBox(did);

	return;