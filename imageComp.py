try:
    from itertools import izip
except ImportError:
    izip = zip

try:
    from PIL import Image
except ImportError:
    import Image

import os, sys

#######################
#Phase one: Resize all images on target folder
#######################

cwd = os.getcwd()+'/images/'
for imgName in os.listdir(cwd):
	img = Image.open(cwd+imgName)
	img = img.resize((1000,1000),Image.ANTIALIAS);
	img.save(cwd+imgName);

print("Redimensionnement terminé")

#######################
#End of phase one
#######################

try:
	imagePath = sys.argv[1]
except IndexError:
	print("No image path was added in the arguments")


i1 = Image.open(imagePath)
bestfitpercent = 0
bestfitpath= ""
for imgName in os.listdir(cwd):
	i2 = Image.open(cwd+imgName)
	assert i1.mode == i2.mode, i1.mode+" "+i2.mode+"Different kinds of images."

	assert i1.size == i2.size, "Different sizes."
	 


	pairs = zip(i1.getdata(), i2.getdata())
	if len(i1.getbands()) == 1:
	    dif = sum(abs(p1-p2) for p1,p2 in pairs)
	else:
	    dif = sum(abs(c1-c2) for p1,p2 in pairs for c1,c2 in zip(p1,p2))
	 
	ncomponents = i1.size[0] * i1.size[1] * 3
	percent = (((dif / 255.0 * 100) / ncomponents)-100)*(-1)
	print("Difference (percentage):", percent)

	if(percent >= bestfitpercent):
		bestfitpercent = percent
		bestfitpath = cwd+imgName

print("The best fit is: <<"+bestfitpath+">> with a resemblance probability of: "+str(bestfitpercent)+"%")
