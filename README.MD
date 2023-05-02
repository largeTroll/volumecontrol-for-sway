Message Box for sway

## Intention
This project is intended to provide an executable, that makes the classical audiosymbol when pressing the volume-up key, or any key, that is associated to it. Therefore it reads out the value of the audio device, specified in the config file. Remember, that this program can - up to this stage - only get the volume from `amixer`. If you haven't installed it, the program won't run.
### Dependencies
There are some factors, you need to keep attention to: You can only compile and/or run the program if you have already installed GLFW3 AND OpenGL. Also, please place the shader files in a folder called 'res' in the same location as the executable and keep in mind, that I'm using `light` to retrieve the display brightness. If you haven't installed it, please do so and you might want to add your user to the group 'video'.
So all in all, you need to run the following commands as root in terminal:
```
sudo apt install amixer light

sudo usermod -a -G video $USER
```

### Swaysetup
Since this is a sway application, you need to do the following:
Please go to the config file of sway (usually in `/etc/sway/`, to make any changes, copy to `~/.config/sway/`) and add the following lines to it:

```
# Set up the correct folder and files for the messagebox and execute it.
# You need to add either 'audio' or 'light' after it
set $messagebox cd /home/domax/.config/sway/messagebox && ./main

### Brightness
# You can change the brightness with the brightnesskeys.
# Use light -A 30 to increase the brightness by 30
# Use light -U 30 to decrease the brightness by 30
set $brightness_up light -r -A 30 && $messagebox "light"
set $brightness_down light -r -U 30 && $messagebox "light"

bindsym --locked XF86MonBrightnessUp exec $brightness_up
bindsym --locked XF86MonBrightnessDown exec $brightness_down

### Volume control
# With the Functionkeys, you are able to control the Volume of the speakers
set $volume_up amixer -q -c 0 -- sset Master 2%+ && $messagebox "audio"
set $volume_down amixer -q -c 0 -- sset Master 2%- && $messagebox "audio"
set $volume_mute amixer -q -c 0 -- sset Master toggle

bindsym --locked XF86AudioRaiseVolume exec $volume_up
bindsym --locked XF86AudioLowerVolume exec $volume_down
bindsym --locked XF86AudioMute exec $volume_mute
```
Note: I'm using the appropriate function keys for sound/backlight control. If this shouldn't work, try pressing the corresponding key and the function key at once. If that also fails, change the keycombination to `$mod+Alt+Right` or somewhat similar and try again.

As you can see in the config file, I am using the Master control in amixer. There is plenty of discussion, what should be inserted here, but I felt best with Master.
If you think, the brightness changes too fast, decrease the value after the light command.

### Configfile
I've included a example config file in the root directory in the repository. Up to now, my code looks for the file `/home/$USER/.config/msgbox/config.conf`. As normal for a config file, you uncomment a line with a '#'. For variables,

I'm pretty sure, that this constellation is not perfect, since I'm learning to code, but I'm satisfied with the result.