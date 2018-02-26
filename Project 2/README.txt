I want to make 3 comments about our submission.

1. When creating the diff, it seems that there is some stuff that escapes the clean and mrproper commands,
which bloats the diff with unrelated stuff. I have that diff, and also another one with that junk removed for your convenience, leaving only our changes to the kernel.

2. In the process of testing for the module, it became tedious to constantly make, remove, and reload it,
so I made a script called run.sh that does all that for me.

3. In the same vein with the syscall, it became tedious to do all the steps to get the kernel loaded,
so I packaged it into another script, go.sh. I have left this and the run.sh in their relative directories 
for completeness' sake.
