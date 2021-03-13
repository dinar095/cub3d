#include "./game/ft_game.h"

t_cord   crc(t_cord a, t_cord b, t_cord dot_a, t_cord dot_b)//точка пересечения по точке и вектору
{
	t_cord dot_c;
	double  q;
	double  n;

	if (dot_b.x == dot_a.x && dot_b.y == dot_a.y)
	    return (dot_b);
	ft_bzero(&dot_c, sizeof(t_cord));
	if (a.y != 0)
	{
	    if (a.y == 0)
        {
	        write(0, "1", 1);
        }
		q = - a.x / a.y;
		n = ((dot_b.x - dot_a.x) + q * (dot_b.y - dot_a.y)) /
			(b.x + b.y * q);
	}
	else if (b.y != 0)
		n = (dot_b.y - dot_a.y) / b.y;
	else
	{
		ft_putstr_fd("Not cross", 1);
		return (dot_a); // Затычка!!!!!!!!!!!!!!
	}
	dot_c.x = dot_b.x - n * b.x;
	dot_c.y = dot_b.y - n * b.y;
	return (dot_c);
}
double angle(t_cord begin, t_cord end)
{
	double q;
	double a;
	double b;
	q = begin.x * end.x + begin.y*end.y;//скалярное произведение векторов
	a = sqrt(pow(begin.x, 2) + pow(begin.y,2));
	b = sqrt(pow(end.x, 2) + pow(end.y,2));
	q = q / (a * b);
	return (q);
}
t_cord rotateZ(t_cord vector,double angle)
{ // angle in radians

//normalize(vector); // No  need to normalize, vector is already ok...
	t_cord tmp;
	tmp.x = (vector.x * cos(angle) - vector.y * sin(angle));

	tmp.y = (vector.x * sin(angle) + vector.y * cos(angle));

	return (tmp);
}
double len_ray(t_cord ray1, t_cord ray2)
{
	return (sqrt(pow(ray1.y - ray2.y, 2) + pow(ray1.x - ray2.x, 2)));
}
//void         drop_rays(t_all *all)
//{
//    t_ray      ray;
//    double      cam;
//
//    ray.x = 0;
//    while (ray.x < all->textures.width)
//    {
//        //ray.slist = NULL;
//        cam = 2 * ray.x / (double)all->textures.width - 1;
//        ray.dir.x = all->plr.dir.x + cam * all->plr.dir.x;
//        ray.dir.y = all->plr.dir.y + cam * all->plr.dir.y;
//        count_ray_len(all, &ray);//ПУскаем луч
//        ray.perp = ray.dist * v_mult(ray.dir, all->player.dir)/v_len(all->player.dir) / v_len(ray.dir);//Избавляемся от фишай
//        draw_strip(all, &ray);//
//        ray.x++;
//    }
//    draw_sprites(all);
//}
t_cord net_point(t_cord ray, t_cord pos)
{
    t_cord tmp;
    if (ray.x > 0)
        tmp.x = ceil(pos.x);
    if (ray.x <= 0)
        tmp.x = floor(pos.x);
    if (ray.y > 0)
        tmp.y = ceil(pos.y);
    if (ray.y <= 0)
        tmp.y = floor(pos.y);
    return (tmp);
}
t_cord fwd_pnt(t_cord ray, t_cord pnt, int flag)
{
    if (flag > 0)
    {
        if (ray.x > 0)
            pnt.x++;
        if (ray.x < 0)
            pnt.x--;
    }
    else
    {
        if (ray.y > 0)
            pnt.y++;
        if (ray.y < 0)
            pnt.y--;
    }
    return (pnt);
}
void print_wall(t_cord plr,t_cord cross, t_textures textures, t_all *all, int x, t_cord ray, int col)
{
	double d_to_wall;
	double y0;
	double y1;
	double h;
	double i;

	i = 0;
	d_to_wall = len_ray(plr, cross) * angle(all->plr.dir, ray);

	h = textures.height/(d_to_wall);
	y0 = textures.height/2 - h/2;
	y1 = textures.height/2 + h/2;
	while (i <= textures.height)
	{
		if (i >= y0 && i <= y1)
		{
			my_mlx_pixel_put(all, x, i, col);
		}
		i++;
	}

//	mlx_put_image_to_window(all->win->mlx, all->win->mlx_win, all->win->img, 0, 0);
}
//void init_texture();
void draw_screen(t_all *all)
{
	t_cord b_x = {0, 1};//вектор по x
	t_cord b_y = {1, 0};//вектор по y
	t_cord cross;
	t_cord cross_x;//вектор пересечения луча и х координаты

	t_cord dot_b;//точка на векторе сетки

	t_cord ray;
	int i = 0;

	char **map = all->map;
	mlx_destroy_image(all->win->mlx, all->win->img);
	init_img(all);
	scale_pix(all, map);
	int col;
	float angel;
	angel = 46 * M_PI/180;
	ray = rotateZ(all->plr.dir, -angel/2);
	while (i < all->textures.width)//привязать к ширине экрана
	{

        dot_b = net_point(ray, all->plr.pos);//точка пересечения сетки
		cross = all->plr.pos;
		while (!(is_wall_cord(map, cross, ray)))
		{
                cross_x = crc(ray, b_x, all->plr.pos, dot_b);//точка пересечения по х
                cross = crc(ray, b_y, all->plr.pos, dot_b);//точка пересечения по у
			if (len_ray(all->plr.pos, cross_x) < len_ray(all->plr.pos, cross))//если по х ближе чем по у
			{
				col = 0xFFFF00;
				cross = cross_x;
				dot_b = fwd_pnt(ray, dot_b, 1);
			}
			else //Если у ближе чем х
			{
				col = 0x858585;
                dot_b = fwd_pnt(ray, dot_b, -1);
			}
			my_mlx_pixel_put(all, cross.x * SCALE, cross.y * SCALE, col);
		}

		print_wall(all->plr.pos, cross, all->textures, all, i, ray, col);
        ray = rotateZ(ray, (angel)/all->textures.width);
		i++;

	}
	mlx_put_image_to_window(all->win->mlx, all->win->mlx_win, all->win->img, 0, 0);
}


int             key_hook(int keycode, t_all *all)
{
   // printf("Keycode: %d\n", keycode);
    if (keycode == W)
		all->plr.pos.y -= 0.25;
	if (keycode == S)
		all->plr.pos.y += 0.25;
	if (keycode == A)
		all->plr.pos.x -= 0.25;
	if (keycode == D)
		all->plr.pos.x += 0.25;
	if (keycode == LEFT)
		all->plr.dir = rotateZ(all->plr.dir, -0.1);
	if (keycode == RIGHT)
		all->plr.dir = rotateZ(all->plr.dir, 0.1);
//	mlx_hook(all->win->mlx_win, 2, 1L<<0, key_hook, &all);
    draw_screen(all);

}

int main(int argc, char **argv) {
    t_textures textures;
    t_data img;
    t_all all;
    t_plr plr;
    if (!open_file(argv[1], &textures))
        return (0);
    all.textures = textures;

	all.plr.pos.x = 10;
	all.plr.pos.y = 5;
	all.plr.dir.x = 0;
	all.plr.dir.y = -1;

	all.win = &img;


	all.map = textures.map;
	img.mlx = mlx_init();
	img.mlx_win = mlx_new_window(img.mlx, textures.width, textures.height, "Cub3d!");
	init_texture();
    init_img(&all);
	draw_screen(&all);

   // mlx_key_hook(img.mlx_win, key_hook, &all);
 	//mlx_loop_hook(all.win->mlx, draw_screen, all.win);
    mlx_hook(all.win->mlx_win, 2, 1L<<0, key_hook, &all);


	mlx_loop(all.win->mlx);
	return 0;
}
