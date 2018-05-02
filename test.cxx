#include <iostream>
#include <fstream>
//using std::ifstream;

#include <sstream>
//using std::ostringstream;

#include <string>
//using std::string;
#include <cstdio>
#include <stdlib.h>

#include <vector>

#include "db_conn.hxx"

using namespace std;

int main(int argc, char **argv) {
   MYSQL_RES *result;
   MYSQL_ROW row;
   int num_fields;
   int num_rows;
   //long *length;
   int i;//for rows
   int j;//for fields
	string dir_name;

   printf("---Program started---\n");
   //set up connection and connect to database ------ this works
   set_db_info_filename(argv[1]);
   initialize_exact_database();
   printf("......You are connected to the database!\n");

   //execute query to get data from mosaics and lines
/*   string query = "select distinct mosaics.id, mosaics.filename, mosaics.height, mosaics.width, mosaics.channels, `lines`.x1, `lines`.x2, `lines`.y1, `lines`.y2 from mosaics, `lines` where mosaics.owner_id=1;"*/

   //execute query to get data from mosaics
   string query = "select id,owner_id,filename,height,width,channels from mosaics where owner_id=1";
   mysql_query(exact_db_conn,query.c_str());
   result = mysql_store_result(exact_db_conn);

   num_rows = mysql_num_rows(result);
   num_fields = mysql_num_fields(result);
   vector< vector<string> > image_data((int)num_rows, vector<string>((int)num_fields));

/* row[0] = id
	row[1] = owner_id
   row[2] = filename
   row[3] = height
   row[4] = width
   row[5] = channels
   ***all are originally strings****/

   //put query results inside vector
   for (i = 0;i < (int)num_rows;i++) {
      row = mysql_fetch_row(result);
      for (j = 0;j < (int)num_fields;j++) {
         image_data[i][j] = row[j];
      }
   }

	printf(".........vector \"image_data\" is populated!\n");

   mysql_free_result(result);

   //execute query to get data from lines
   query = "select mosaic_id,x1,x2,y1,y2 from `lines` where owner_id=1";
   mysql_query(exact_db_conn,query.c_str());
   result = mysql_store_result(exact_db_conn);

   num_rows = mysql_num_rows(result);
   num_fields = mysql_num_fields(result);
   vector< vector<string> > line_data((int)num_rows, vector<string>((int)num_fields));

/* row[0] = mosiac_id
   row[1] = x1
   row[2] = x2
   row[3] = y1
   row[4] = y2
   ***all are originally strings****/

   //put quiery results inside vector
   for (i = 0;i < (int)num_rows;i++) {
      row = mysql_fetch_row(result);
      for (j = 0;j < (int)num_fields;j++) {
         line_data[i][j] = row[j];
      }
   }

   printf(".........vector \"line_data\" is populated!\n");

   mysql_free_result(result);

	//connect to /mosaic_uploads/ directory
   printf("---Program ends---\n");

   return 0;
}


