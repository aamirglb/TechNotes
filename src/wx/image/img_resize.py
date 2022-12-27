import os
from PIL import Image

dir_path = r'C:/Users/aamir.ali/Pictures/demo-lib/'
result = []

for path in os.listdir(dir_path):
    if os.path.isfile(os.path.join(dir_path, path)):
        name, ext = os.path.splitext(path)
        if ext != '.jpg':
            continue

        full_path = dir_path + path
        image = Image.open(full_path)
        image.thumbnail((256, 256))
        
        new_name = dir_path + "thumbnail/" + name + "_256x256" + ext
        image.save(new_name)
        print('{} => {}'.format(new_name, image.size))


