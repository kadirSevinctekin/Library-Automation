# Subject: Library Automation Application based on the working principles of relational databases, small-scale and file processing-oriented.

Functional Requirements:
1- Author Addition/Deletion/Editing/Listing Operations: Each author should have a first name, last name, and a unique authorID value assigned 
automatically in ascending order (1, 2, ..., N) based on the authorID in a SINGLY LINKED LIST. This information should be stored in a file 
named "yazarlar.csv." The user should be able to delete or edit these stored author information if desired, and the updated information should 
be reflected in the same file.

2- Student Addition/Deletion/Editing/Listing Operations: Each student should have a first name, last name, an initially assigned library score of 100, 
and a unique 8-digit student number. The information related to students should be stored in a DOUBLY LINKED LIST and a file named "Ogrenciler.csv" 
using a defined struct within the application. The user should be able to delete or edit these stored student information if desired, and the updated
information should be reflected in the same file.

3- Book Addition/Deletion/Editing/Listing Operations: Each book should have a title, a 13-digit ISBN number, and a quantity value. Since there can be
multiple copies of a book in the library, a unique tag number should be automatically assigned to each copy during the record creation, appended with 
a number (ISBN_1, ISBN_2, ISBN_N) based on the ISBN number. The books should be stored in a SINGLY LINKED LIST (struct Kitap) based on their titles 
and ISBN numbers. Additionally, for each book, a SINGLY LINKED LIST (struct KitapOrnek) should be created to store the information about each copy of 
the book, including the tag number and the borrowing status. In this context, if a book is borrowed, the ID number of the student who borrowed it 
should be recorded. If the book is not borrowed, the status should be indicated as "RAFTA" (on the shelf) in this field. The relationship between 
each BOOK and its copies should be modeled using SINGLY LINKED LISTS as shown in Figure 1, and this data should be stored in CSV files consistently. 
A CSV file is a text file where each data entry is separated by a comma (,).
Example: Java Programming, 1234567891011, 5
