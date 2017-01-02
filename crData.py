#!/usr/bin/python
import random

nColleges = 1000
nStudents = 250000
r = random.SystemRandom()
letters = 'abcdefghijklmnopqrstuvwxyz'
# Percentage distribution of marks:
#TODO
#For colleges
with open('sandbox/colleges.csv', 'w') as cfile:
	for i in range(1, nColleges + 1):
		cfile.write(str(i))
		cfile.write(',')
		cfile.write(''.join(letters[r.randint(0,25)] for n in range(6)))
		cfile.write(',')
		cfile.write(str(r.randint(95,105)))
		cfile.write('\n')
# For students
with open('sandbox/students.csv', 'w') as sfile:
	for i in range(0, nStudents):
		sfile.write(str(r.randint(200,500)))
		sfile.write(',')
		sfile.write(str(i))
		sfile.write(',')
		sfile.write(str.capitalize(''.join(letters[r.randint(0,25)] for n in range(5))))
		sfile.write(' ')
		sfile.write(str.capitalize(''.join(letters[r.randint(0,25)] for n in range(5))))
		sfile.write(',')
		prefnums = [r.randint(1, nColleges) for n in range(5)]
		prefs = str(prefnums[0])
		for j in range(4):
			prefs += ';' + str(prefnums[j+1])
		sfile.write(prefs)
		sfile.write('\n')
print("Created files in sandbox folder.")
