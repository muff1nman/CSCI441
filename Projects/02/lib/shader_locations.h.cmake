/*
 * shader_locations.h
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#ifndef __shader_locations_h__
#define __shader_locations_h__

#define SHADER_DIR "${SHADER_OUTPUT_DIR}/"

#define FLAT_VERTEX_SHADER_NAME "flat_vertex.glsl"
#define FLAT_FRAGMENT_SHADER_NAME "flat_fragment.glsl"

#define FLAT_VERTEX_SHADER SHADER_DIR FLAT_VERTEX_SHADER_NAME
#define FLAT_FRAGMENT_SHADER SHADER_DIR FLAT_FRAGMENT_SHADER_NAME

#define GOURAUD_VERTEX_SHADER_NAME "gouraud_vertex.glsl"
#define GOURAUD_FRAGMENT_SHADER_NAME "gouraud_fragment.glsl"

#define GOURAUD_VERTEX_SHADER SHADER_DIR GOURAUD_VERTEX_SHADER_NAME
#define GOURAUD_FRAGMENT_SHADER SHADER_DIR GOURAUD_FRAGMENT_SHADER_NAME

#define PHONG_VERTEX_SHADER_NAME "phong_vertex.glsl"
#define PHONG_FRAGMENT_SHADER_NAME "phong_fragment.glsl"

#define PHONG_VERTEX_SHADER SHADER_DIR PHONG_VERTEX_SHADER_NAME
#define PHONG_FRAGMENT_SHADER SHADER_DIR PHONG_FRAGMENT_SHADER_NAME

#endif /* !__shader_locations_h__ */

