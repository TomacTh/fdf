# fdf

# INSTALL

## Install mini libx in /usr/local/lib copy mlx.h header in /usr/local/include
#### linux: https://github.com/42Paris/minilibx-linux
#### mac: https://github.com/dannywillems/minilibx-mac-osx

Copy minilibx.a in **/usr/local/lib** and copy mlx.h header in **/user/local/include**

If you are in mac os change LDFLAGS in make file to:   -framework OpenGL -framework Appkit

With make bonus you can zoom dezoom translate map and change projection, also change z depth;

* 'd': less depth z
* 'z': more z depth
* '+'(same than =key): zoom
* '-'(same than 6key): dezoom'
* 'p': change projection parallel to iso
* arrows translate your map;

For mac os change value Of keys in fdf_bonus.h
![Screenshot from 2022-11-08 12-03-43](https://user-images.githubusercontent.com/43377611/200549406-872163da-1acf-4134-aa72-615072e55c6d.png)