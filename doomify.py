from PIL import Image
from pallete import *
import os

def GetClosestColor(color,palette):
    closest_index = 0
    closest_color_difference = 0

    current_index = 0
    for c in palette:
        if current_index == 0:
            closest_color_difference = GetTotalRGBDifference(color,c)
            closest_index = 0
        else:
            current_color_difference = GetTotalRGBDifference(color,c)
            if current_color_difference < closest_color_difference:
                closest_color_difference = current_color_difference
                closest_index = current_index
        current_index += 1
    return palette[closest_index]

def GetTotalRGBDifference(color1,color2):
    difference = 0
    difference += abs(color1[0] - color2[0])
    difference += abs(color1[1] - color2[1])
    difference += abs(color1[2] - color2[2])
    return difference

def GetDictionaryValueFromUser(prompt,dictionary):
    print(prompt)
    for k in dictionary:
        print("{} : {}".format(k,dictionary[k][0]))
    selection_is_valid = False
    selection = ""
    while not selection_is_valid:
        selection = input()
        try:
            selection = dictionary[selection][1]
            selection_is_valid = True
        except KeyError:
            print("Please enter a listed selection.")
    return selection

#Start of program
palettes = {"1":("DOOM",DOOM),"2":("QUAKE",QUAKE)}
source_paths = input("Enter or drag image file path(s): ")
source_paths = source_paths.split()
if len(source_paths) == 0:
    exit
for path in source_paths:
    source_image = Image.open(path)
    selected_palette = GetDictionaryValueFromUser("[{}]\n Please select a color paltte:".format(path),palettes)
    source_image = source_image.resize((64,64),Image.NEAREST)
    #This is needed for image formats that use a color table/palette.
    source_image = source_image.convert("RGBA")
    result = Image.new("RGB",source_image.size,color=(0,255,255))

    print("Processing {} ...".format(path))
    for i in range(source_image.size[0]):
        for ii in range(source_image.size[1]):
            source = source_image.getpixel((i,ii))
            source_r,source_g,source_b = source[0],source[1],source[2]
            if len(source) > 3: #alpha channel exists
                if source[3] < 128:
                    closest_color = (0,255,255)
                else:
                    closest_color = GetClosestColor((source_r,source_g,source_b),selected_palette)
            else:
                closest_color = GetClosestColor((source_r,source_g,source_b),selected_palette)
            result.putpixel((i,ii),closest_color)
    print("DONE!")

    source_image.close()

    output_path = os.path.join(os.getcwd(),"output")
    if not os.path.isdir(output_path):
        os.mkdir(output_path)

    output_name = os.path.basename(path)
    output_name = output_name.replace(".","_")
    result.save(os.path.join(output_path,"doomify_{}.bmp".format(output_name)),format="bmp")