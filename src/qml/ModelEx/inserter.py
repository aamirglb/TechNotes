import csv
import sqlite3

def read_city_list():
    with open('city.csv') as f:
        reader = csv.reader(f, delimiter=",")
        cnt = 0
        for row in reader:
            if cnt != 0:
                yield (row[0], row[1])
                # print(f'{cnt+1}. {row[0]} => {row[1]}')
            cnt += 1

def create_connection(db_file):
    connection = None
    try:
        connection = sqlite3.connect(db_file)
    except sqlite3.Error as e:
        print(e)
    return connection

def insert_city(connection, city_country):
    sql = '''
        INSERT INTO city (
            capital,
            country
        )
        VALUES (?, ?)
    '''
    cursor = connection.cursor()
    cursor.execute(sql, city_country)
    connection.commit()
    return cursor.lastrowid

def main():
    database = 'cities.db'
    connection = create_connection(database)

    with connection:
        for t in read_city_list():
            insert_city(connection, t)


if __name__ == '__main__':
    main()