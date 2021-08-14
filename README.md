# fdf

# INSTALL

## Install mini libx in /usr/local/lin copy mlx.h header in /usr/local/include
#### linux: https://github.com/42Paris/minilibx-linux
#### mac: https://github.com/dannywillems/minilibx-mac-osx

If you are in mac os change LDFLAGS in make file to:   -framework OpenGL -framework Appkit

With make bonus you can zoom dezoom translate map and change projection, also change z depth;

* 'd': less depth z
* 'z': more z depth
* '+'(same than =key): zoom
* '-'(same than 6key): dezoom'
* 'p': change projection parallel to iso
* arrows translate your map;

For mac os change value Of keys in fdf_bonus.h
