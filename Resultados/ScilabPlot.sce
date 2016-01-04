//Scilab commands to visualize the results
//Comandos no Scilab para visualizar os resultados

//Grid
//Malha
iM=48
jM=48

//U vertical velocity profile  and V horizontal velocity profile
//Perfil vertical da velocidade U e perfil horizontal da velocidade V
z = linspace(0,1,iM+2);
plot(z,U(floor(iM)/2,:))
plot(z,V(:,floor(iM)/2))


/U & V vector field plot
//Plot do campo vetorial U e V
UFull=U;VFull=V;
UFull(:,jM+1)=(UFull(:,jM+1)+UFull(:,jM+2))/2; UFull(:,jM+2)=[];
VFull(iM+1,:)=(VFull(iM+1,:)+VFull(iM+2,:))/2; VFull(iM+2,:)=[];

x = linspace(0,1,iM+1); y = linspace(0,1,jM+1);
[X,Y]=meshgrid(x,y);
scf(42); clf(42);
f=gcf();
f.color_map=jetcolormap(128);
colorbar(-0.5,0.5)
champ1(x,y,UFull,VFull,rect=[-0.01, -0.01,1.01,1.01], arfact=1)

//Colorplot U
x = linspace(0,1,iM+1); y = linspace(0,1,jM+1);
f=gcf();
f.color_map=jetcolormap(128);
colorbar(-0.5,0.5)
Sgrayplot(x,y,UFull, strf="042", zminmax=[-0.5,1])

//Colorplot V
x = linspace(0,1,iM+1); y = linspace(0,1,jM+1);
f=gcf();
f.color_map=jetcolormap(128);
colorbar(-0.5,0.5)
Sgrayplot(y,x,VFull, strf="042", zminmax=[-0.5,1])

