#include <stdio.h>           // Input/Output
#include <stdlib.h>          // Memory Allocation
#include <libpq-fe.h>        // PostgreSQL library for C

int main() {
    const char *conninfo;
    PGconn *conn;
	
    // Connect to the database
    conninfo = "host=localhost port=5432 dbname=testdb user=postgres";

    conn = PQconnectdb(conninfo);

    // Check if the connection to the database was successful
    if (PQstatus(conn) != CONNECTION_OK) {
        fprintf(stderr, "Connection to database failed: %s", PQerrorMessage(conn)); // Print error message
        PQfinish(conn);   // Close connection and exit if failed
	exit(1);  	  // Exit
    }

    // Take data
    PGresult *res = PQexec(conn, "SELECT * FROM Student");

    // Check if the data was taken from PostgreSQL
    if (PQresultStatus(res) != PGRES_TUPLES_OK) {
        fprintf(stderr, "SELECT failed: %s", PQerrorMessage(conn)); // Print error message
        PQclear(res);         // Clear result object
        PQfinish(conn);
	exit(1);
    }

    // Get the number of rows and columns in the result
    int rows = PQntuples(res);  // Get the number of rows
    int cols = PQnfields(res);  // Get the number of columns

    // Loop through each element
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%s\t", PQgetvalue(res, i, j)); // Print the value of each cell
        }
        printf("\n");        // Make it pretty
    }

    PQclear(res);             // Clear the result object
    PQfinish(conn);           // Close the connection to the database
    return 0;                 // Return success status
}

