# FDF

#### *The scope of the project is defined* [here](https://cdn.intra.42.fr/pdf/pdf/52998/en.subject.pdf)

## **To install minilibx:**
- linux: https://github.com/42Paris/minilibx-linux
- mac: https://github.com/dannywillems/minilibx-mac-osx
- Then copy `libmlx.a` in `/usr/local/lib` and copy `mlx.h` header in `/user/local/include`

## **Mac os**
- If you are in mac os change `LDFLAGS` in `Makefile` to:   *-framework OpenGL -framework Appkit*
- For mac os change value Of keys in fdf_bonus.h

## **Keys**
With `make bonus` you can zoom, dezoom, translate map, change projection, and change z depth;

* 'd': - depth z
* 'z': + z depth
* '+'(same than =key): zoom
* '-'(same than 6key): dezoom
* 'p': change projection parallel to iso
* '↓→↑←': translate your map;




![Screenshot from 2022-11-08 12-03-43](https://user-images.githubusercontent.com/43377611/200549406-872163da-1acf-4134-aa72-615072e55c6d.png)
![Screenshot from 2022-11-08 12-04-52](https://user-images.githubusercontent.com/43377611/200549551-df1c4579-6dbd-4b66-b1dc-43e3f5d385ce.png)
![Screenshot from 2022-11-08 12-05-04](https://user-images.githubusercontent.com/43377611/200549556-92b3f7b8-7929-41d4-8274-28bd06d64181.png)
![Screenshot from 2022-11-08 12-06-42](https://user-images.githubusercontent.com/43377611/200549561-21efb061-51c5-47bc-a8a9-2f3f54ce49aa.png)

![68747470733a2f2f692e696d6775722e636f6d2f75755a45644a622e706e67](https://user-images.githubusercontent.com/43377611/200590144-30b9a28e-494f-4cb9-81bf-fa5cb0ec3a54.png)

