#pragma once

void setCameraPosition(vec3 newPosition);

void addToCameraPosition(vec3 positionToAdd, float multiplier);

void getCameraPosition(vec3 cameraPosition);

void setCameraDirection(vec3 newDirection);

void getCameraDirection(vec3 cameraDirection);

void updateCamera();
