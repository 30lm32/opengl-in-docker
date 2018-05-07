IMAGE_NAME=opengl

build:
	docker build -t ${IMAGE_NAME} .
run_Ike_Moisha_Broflovski:
	docker run -ti --rm \
		-e DISPLAY=${DISPLAY} \
		-v /tmp/.X11-unix:/tmp/.X11-unix \
		${IMAGE_NAME} \
		./bin/Ike_Moisha_Broflovski.bin

run_3D_William_Tell:
	docker run -ti --rm \
		-e DISPLAY=${DISPLAY} \
		-v /tmp/.X11-unix:/tmp/.X11-unix \
		${IMAGE_NAME} \
		./bin/3D_William_Tell.bin
