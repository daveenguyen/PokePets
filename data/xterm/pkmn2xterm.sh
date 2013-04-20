# script by davee
# download the overworld sprites from veekun
# and img2xterm from rossy2401@github.com
mkdir front
mkdir back

max=151
for i in `seq 1 $max`
do
    ./img2xterm "overworld/down/$i.png" > "front/$i.xterm"
    ./img2xterm "overworld/up/$i.png" > "back/$i.xterm"
done