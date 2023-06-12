CREATE TABLE students (
    id INTEGER,
    student_name TEXT,
    PRIMARY KEY(id)
);
CREATE TABLE houses (
    house TEXT,
    head TEXT,
    PRIMARY KEY(house)
);
CREATE TABLE assignments (
    student_id INTEGER,
    house_id TEXT,
    FOREIGN KEY(student_id) REFERENCES students(id),
    FOREIGN KEY(house_id) REFERENCES houses(house),
    PRIMARY KEY(student_id, house_id)
);
