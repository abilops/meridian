#Meridian
Meridian is created to solve the problem of allocating low-supply things that have a high demand.
Applications include (but are not limited to):
  + Students applying for college. Merit based on marks
  + Auctions?
  + Can't think of anything else right now

Proposed design for the working of Meridian:
  + Independent files contain specific data.
  + COLLEGES.dat (called 'c' for easy typing): Contains list of colleges with ID's and number of seats
  + `STUDENTS.dat` (called 's' for easy typing): Contains list of students with ID's, preferences and marks

	Meridian will first load `STUDENTS.dat` into memory and sort it in descending order of marks.
	This new data will be added to a file called `STUDENTS-s.dat`
	
	Then it will make a copy of COLLEGES.dat called `COLLEGES-r.dat`. This file will be the data for the number of seats remaining in each college (if any).
	Then it will iterate through this list of students, from top to bottom, and start allocating him/her their first preferred college.
	If there are no remaining seats, it will jump to the next preference.
	Once a students fate is decided, the `RESULTS.dat` file will be appended with the ID NAME and ALLOCATED data.
	The seats remaining in the college are updated (it is best that the changes are not written to the file one at a time).
	There will also be another file that gives a list of students allocated to a college. But this is not a priority now.

	Once, either every available seat is taken or all students are done, the process exits, leaving `STUDENTS-s.dat`, `COLLEGES-r.dat` and more importantly, `RESULTS.dat` in its wake. This file will be a CSV for easy printing and importing in Microsoft Excel.

	Meridian will be designed not to make changes to the input files at all. It will be as lightweight as possible.
