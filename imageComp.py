try:
    from itertools import izip
except ImportError:
    izip = zip

try:
    from PIL import Image
except ImportError:
    import Image

import os, sys


try:
 	subjectPath = sys.argv[2]
except IndexError:
 	print("No image folder was given to search in second second arguement")

try:
	imagePath = sys.argv[1]
except IndexError:
	print("No image path was added in the arguments")


cwd = os.getcwd()+'/photos/'+subjectPath+'/'

i1 = Image.open(imagePath) #Open image to search for
bestfitpercent = 0 
bestfitpath= ""
for imgName in os.listdir(cwd): #Loop through faces in images directory
	i2 = Image.open(cwd+imgName)
	#assert i1.mode == i2.mode, i1.mode+" "+i2.mode+"Different kinds of images." # Make sure the two photos have the same type

	assert i1.size == i2.size, "Different sizes." # Make sure the two photos have the same size
	 
	#Alortithm to find the difference between the photo in param and the photos in the list
	pairs = zip(i1.getdata(), i2.getdata()) 
	if len(i1.getbands()) == 1:
	    dif = sum(abs(p1-p2) for p1,p2 in pairs)
	else:
	    dif = sum(abs(c1-c2) for p1,p2 in pairs for c1,c2 in zip(p1,p2))
	 
	ncomponents = i1.size[0] * i1.size[1] * 3
	percent = (((dif / 255.0 * 100) / ncomponents)-100)*(-1)

	if(percent >= bestfitpercent):
		bestfitpercent = percent
		bestfitpath = cwd+imgName


print(bestfitpercent)
