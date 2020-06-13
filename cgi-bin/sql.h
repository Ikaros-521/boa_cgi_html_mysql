#ifndef SQL_H
#define SQL_H
 
#include <iostream>
#include <vector>
#include <stdio.h>
#include <stdint.h>
#include <mysql/mysql.h>

using namespace std;

class SQL
{
	MYSQL* conn;
	bool isAutoCommit;
	vector<vector<string> > result; 
	
public:
	SQL(void);
	
	SQL(const char* ip,const char* user,const char* passwd,const char* database,uint16_t port);
	
	~SQL(void);
	
	bool connect(const char* ip,const char* user,const char* passwd,const char* database,uint16_t port);
	
	int insert(const char* cmd);
	int remove(const char* cmd);
	int update(const char* cmd);
	int select(const char* cmd);
	
	void clearResult(void);
	
	void showResult(void);
	
	bool offAutoCommit(void);
	bool onAutoCommit(void);
	bool getAutoCommit(void);
};

#endif//SQL_H
