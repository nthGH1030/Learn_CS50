import csv
from cs50 import SQL

def main():
    students = []
    houses = []
    #read the csv file into a list of dictionary
    with open('students.csv', 'r') as csvfile:
        reader = csv.DictReader(csvfile)
        for row in reader:
            count = 0
            students.append(row)
            for house in houses:
                if row["house"] == house["house"]:
                    count +=1
            if count == 0:
                houses.append({"house": row["house"], "head": row["head"]})

    #for house in houses:
        #print(house)

    db = SQL("sqlite:///roster.db")

    for house in houses:
        db.execute("INSERT INTO houses(house, head) VALUES (?,?)", house["house"], house["head"])

    for student in students:
        db.execute("INSERT INTO students (id, student_name) VALUES (?,?)",int(student["id"]), student["student_name"])

        db.execute("INSERT INTO assignments(student_id, house_id) VALUES (?,?)",int(student["id"]) , student["house"])




        #if(student['house'] == 'Slytherin'):
            #db.execute("INSERT INTO assignments(student_id, house_id) VALUES (?, ?) ",student['id'] , student['house'])
        #elif(student['house'] == 'Ravenclaw'):
            #db.execute("INSERT INTO assignments(student_id, house_id) VALUES (?, (SELECT id FROM houses WHERE house = Ravenclaw)) ",student['id'])
        #elif(student['house'] == 'Gryffindor'):
            #db.execute("INSERT INTO assignments(student_id, house_id) VALUES (?, (SELECT id FROM houses WHERE house = Gryffindor)) ",student['id'])
        #elif(student['house'] == 'Hufflepuff'):
            #db.execute("INSERT INTO assignments(student_id, house_id) VALUES (?, (SELECT id FROM houses WHERE house = Hufflepuff)) ",student['id'])

main()