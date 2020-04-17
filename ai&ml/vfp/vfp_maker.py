from captcha.image import ImageCaptcha
import matplotlib.pyplot as plt
import numpy as np
import random
import cv2
import numpy

# %matplotlib inline
# %config InlineBackend.figure_format = 'retina'

import string
characters = string.digits + string.ascii_uppercase
print(characters)

width, height, n_len, n_class = 170, 80, 4, len(characters)

generator = ImageCaptcha(width=width, height=height)

for i in range(0,499):
    random_str = ''.join([random.choice(characters) for j in range(4)])
    img = generator.generate_image(random_str)

    img2 = cv2.cvtColor(numpy.asarray(img),cv2.COLOR_RGB2BGR)
    cv2.imwrite("./tr-vf/{}.png".format(random_str),img2)

    # plt.imshow(img)
    # plt.title(random_str)
    # plt.show()