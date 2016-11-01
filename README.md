#Meridian
Meridian is created to solve the problem of allocating low-supply things that have a high demand.
Applications include (but are not limited to):
  + Students applying for college. Merit based on marks

Proposed design for the working of Meridian:
  + Independent CSV files contain specific data.
  + One file for the demands, their seats and id
  + Another for the applicants, their deservibility and id

  It will load the applicants, then sort it and save the sorted file in `.tempsorted`.
  After unloading the students from memory, it will load all colleges into memory.
  Then it will read the `.tempsorted` file line-by-line and assign each student a college. Since this file is already sorted, the first priority goes to the person with the highest deservability.
  It will write the results to the results file after each of this iteration, in case `meridian` crashes mid-way.

  Right now, the code works just as a proof of concept. Things that I am working on right now: (`TODO`s are added to the code where necessary)
  + Functions for file-opening, and file-reading (CSV)
  + Hash tables for storing colleges in memory, so that I don't need to iterate over all the colleges, searching for the one matching the id.
  + Add error capturing for unknown IDs, no memory (IMPORTANT for every malloc since this is supposed to handle very very very very large files)

	Meridian will be designed not to make changes to the input files at all. It will be as lightweight as possible
