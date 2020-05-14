import os

results = os.walk(".")
for result in results:
	filenames = result[2]
	for filename in filenames:
		os.system("./../build/afbd " + filename + " main");
