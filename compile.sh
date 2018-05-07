# Building OpenGL/GLUT Programs
# http://web.eecs.umich.edu/~sugih/courses/eecs487/glut-howto/
# Compile
# g++ <Input_File_Name> -o <Output_File_Name> -lGL -lGLU -lglu

ls

g++ ./src/3D_William_Tell.cpp -o ./bin/3D_William_Tell.bin -lGL -lGLU -lglut
echo "3D_William_Tell.bin was compiled"

g++ ./src/Ike_Moisha_Broflovski.cpp -o ./bin/Ike_Moisha_Broflovski.bin -lGL -lGLU -lglut
echo "Ike_Moisha_Broflovski.bin was compiled"

ls ./bin/*.bin
