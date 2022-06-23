/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_operations.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabet <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 21:07:02 by aabet             #+#    #+#             */
/*   Updated: 2021/03/18 21:07:10 by aabet            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structures.h"
#include "../vec_func/vec_func.h"

t_camera	*create_new_camera(t_scene *scene)
{
	t_camera *new;
	t_camera *cur;

	if (!(new = malloc(sizeof(t_camera))))
		return (NULL);
	new->coor = full_vec(0);
	new->vec = full_vec(-2);
	new->fov = -1;
	new->next = NULL;
	if (!scene->camera)
		scene->camera = new;
	else
	{
		cur = scene->camera;
		while (cur->next)
			cur = cur->next;
		cur->next = new;
	}
	return (new);
}

t_light		*create_new_light(t_scene *scene)
{
	t_light *new;
	t_light *cur;

	if (!(new = malloc(sizeof(t_camera))))
		return (NULL);
	new->coor = full_vec(0);
	new->ratio = -2;
	new->color = full_color(-1);
	new->next = NULL;
	if (!scene->light)
		scene->light = new;
	else
	{
		cur = scene->light;
		while (cur->next)
			cur = cur->next;
		cur->next = new;
	}
	return (new);
}

t_elem		*create_new_elem(t_scene *scene, int type)
{
	t_elem *new;
	t_elem *cur;

	if (!(new = malloc(sizeof(t_elem))))
		return (NULL);
	new->type = type;
	new->coor = full_vec(0);
	new->coor2 = full_vec(0);
	new->coor3 = full_vec(0);
	new->coor4 = full_vec(0);
	new->vec = full_vec(-2);
	new->diam = 0;
	new->height = 0;
	new->color = full_color(-1);
	new->next = NULL;
	if (!scene->elems)
		scene->elems = new;
	else
	{
		cur = scene->elems;
		while (cur->next)
			cur = cur->next;
		cur->next = new;
	}
	return (new);
}

t_scene		*create_new_scene(void)
{
	t_scene *scene;

	if (!(scene = malloc(sizeof(t_scene))))
		return (0);
	scene->x_size = 0;
	scene->y_size = 0;
	scene->am_l.color = full_color(-1);
	scene->am_l.ratio = -1;
	scene->camera = NULL;
	scene->light = NULL;
	scene->elems = NULL;
	return (scene);
}

void		delete_scene(t_scene *scene)
{
	void *next;

	if (!scene)
		return ;
	while (scene->camera_list)
	{
		next = scene->camera_list->next;
		free(scene->camera_list);
		scene->camera_list = next;
	}
	while (scene->light)
	{
		next = scene->light->next;
		free(scene->light);
		scene->light = next;
	}
	while (scene->elems)
	{
		next = scene->elems->next;
		free(scene->elems);
		scene->elems = next;
	}
	free(scene);
}
