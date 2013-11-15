/*
 * shader_locations.h
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#ifndef __shader_locations_h__
#define __shader_locations_h__

#define SHADER_DIR "${SHADER_OUTPUT_DIR}/"

#define CARVE_VERTEX_SHADER_NAME "carving_vertex.glsl"
#define CARVE_FRAGMENT_SHADER_NAME "carving_fragment.glsl"

#define CARVE_VERTEX_SHADER SHADER_DIR CARVE_VERTEX_SHADER_NAME
#define CARVE_FRAGMENT_SHADER SHADER_DIR CARVE_FRAGMENT_SHADER_NAME

#define ENVIRONMENT_VERTEX_SHADER_NAME "environment_vertex.glsl"
#define ENVIRONMENT_FRAGMENT_SHADER_NAME "environment_fragment.glsl"

#define ENVIRONMENT_VERTEX_SHADER SHADER_DIR ENVIRONMENT_VERTEX_SHADER_NAME
#define ENVIRONMENT_FRAGMENT_SHADER SHADER_DIR ENVIRONMENT_FRAGMENT_SHADER_NAME

#define DOUGHNUT_VERTEX_SHADER_NAME "doughnut_vertex.glsl"
#define DOUGHNUT_FRAGMENT_SHADER_NAME "doughnut_fragment.glsl"

#define DOUGHNUT_VERTEX_SHADER SHADER_DIR DOUGHNUT_VERTEX_SHADER_NAME
#define DOUGHNUT_FRAGMENT_SHADER SHADER_DIR DOUGHNUT_FRAGMENT_SHADER_NAME

#endif /* !__shader_locations_h__ */

