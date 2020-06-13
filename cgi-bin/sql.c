#include "sql.h"
#include <iomanip>

SQL::SQL(void)
{
    conn = mysql_init(NULL);
    if(NULL == conn)
    {
        printf("errno:%d error:%s\n",mysql_errno(conn),mysql_error(conn));
    }
}
	
SQL::SQL(const char* ip,const char* user,const char* passwd,const char* database,uint16_t port)
{
	conn = mysql_init(NULL);
    if(NULL == conn)
    {
        printf("errno:%d error:%s\n",mysql_errno(conn),mysql_error(conn));
        return;
    }
    
	connect(ip,user,passwd,database,port);
}
	
SQL::~SQL(void)
{

}
	
bool SQL::connect(const char* ip,const char* user,const char* passwd,const char* database,uint16_t port)
{
	if(NULL == mysql_real_connect(conn,ip,user,passwd,database,port,NULL,0))
    {
        printf("---errno:%d error:%s\n",mysql_errno(conn),mysql_error(conn));
        return false;
    }
    
    onAutoCommit();
    
    return true;
}
	
void SQL::clearResult(void)
{
	for(vector<vector<string> >::iterator it = result.begin(); it!=result.end(); it++)
	{
		it->clear();
	}
	
	result.clear();
}

void SQL::showResult(void)
{
	for(vector<vector<string> >::iterator i = result.begin(); i!=result.end(); i++)
	{
		for(vector<string>::iterator j=i->begin(); j!=i->end(); j++)
		{
			cout << setw(12) << *j << "   ";
		}
		cout << endl;
	}
}

int SQL::insert(const char* cmd)
{
	if(mysql_query(conn,cmd) != 0)
	{
		printf("errno:%d error:%s\n",mysql_errno(conn),mysql_error(conn));
		return -1;
	}
	
	return mysql_affected_rows(conn);
}

int SQL::remove(const char* cmd)
{
	if(mysql_query(conn,cmd) != 0)
	{
		printf("errno:%d error:%s\n",mysql_errno(conn),mysql_error(conn));
		return -1;
	}
	
	return mysql_affected_rows(conn);
}

int SQL::update(const char* cmd)
{
	if(mysql_query(conn,cmd) != 0)
	{
		printf("errno:%d error:%s\n",mysql_errno(conn),mysql_error(conn));
		return -1;
	}
	
	return mysql_affected_rows(conn);
}

int SQL::select(const char* cmd)
{
	MYSQL_RES *res;
	MYSQL_ROW row;
	
	if(mysql_query(conn,cmd) != 0)
	{
		printf("errno:%d error:%s\n",mysql_errno(conn),mysql_error(conn));
		return -1;
	}
	
	int num_fields = mysql_field_count(conn);
	if(num_fields == 0)
	{
		printf("errno:%d error:%s\n",mysql_errno(conn),mysql_error(conn));
		return -1;	
	}
	
	res = mysql_store_result(conn);
	if(NULL == res)
	{
		printf("errno:%d error:%s\n",mysql_errno(conn),mysql_error(conn));
		return -1;
	}
	
	clearResult();
	
	int count = 0;
	while((row = mysql_fetch_row(res)))
	{
		vector<string> arr;
		for(int i=0; i<num_fields; i++)
		{
			string str(row[i]);
			arr.push_back(str);
		}
		result.push_back(arr);	
		count++;
	}
	
	mysql_free_result(res);
	return count;
}
	
bool SQL::offAutoCommit(void)
{
	isAutoCommit = false;
	return mysql_autocommit(conn,isAutoCommit);
}

bool SQL::onAutoCommit(void)
{
	isAutoCommit = true;
	return mysql_autocommit(conn,isAutoCommit);
}

bool SQL::getAutoCommit(void)
{
	return isAutoCommit;
}
