# Contribuir al proyecto "AI for Good"
Antes de hacer cualquier contribución al proyecto, favor de leer las siguientes indicaciones para asegurarnos de que el proceso de colaboración sea lo más fluido posible.

## Utilizar los issues como punto de partida
Los issues en este repo indica que es lo mas urgente que se tiene que hacer. Si hay algún objetivo que se tiene que realizar y no estan en los issues, favor de crear un nuevo issue para que el equipo pueda estar al tanto de lo que se tiene que hacer.

A la hora de hacer los issues, habrán distintos tipos de labels que se le pueden atribuir a cada issue, a continuación se muestra una tabla con los distintos tipos de labels y su significado:

| **Label** | **Significado** |
|:---:|:---:|
| <div style="display:inline-flex;align-items:center;justify-content:center;padding:4px 12px;border-radius:999px;background:#3d4245;color:#F5F5DC;border:1px solid #747772;line-height:1;white-space:nowrap;">Bitácora</div>| Este label se utiliza para indicar que el issue es parte de la bitácora del proyecto, es decir, que se trata de una tarea o actividad que se ha realizado durante el desarrollo del proyecto. |
| <div style="display:inline-flex;align-items:center;justify-content:center;padding:4px 12px;border-radius:999px;background:#0b2337;color:#3aadff;border:1px solid #184263;line-height:1;white-space:nowrap;">Documentación</div> | Este label se utiliza para indicar que el issue está relacionado con la documentación del código del proyecto. |
| <div style="display:inline-flex;align-items:center;justify-content:center;padding:4px 12px;border-radius:999px;background:#0d1b3a;color:#94b1f9;border:1px solid #344873;line-height:1;white-space:nowrap;">Paper</div> | Este label se utiliza para indicar que el issue está relacionado con la investigación de papers científicos relacionados con el proyecto. |
| <div style="display:inline-flex;align-items:center;justify-content:center;padding:4px 12px;border-radius:999px;background:#112932;color:#00e8fd;border:1px solid #0c626f;line-height:1;white-space:nowrap;">Código</div> | Este label se utiliza para indicar que el issue está relacionado con la implementación de código para el proyecto. |

## Niveles de urgencia
Cada issue tiene su propio nivel de urgencia, los cuales se separan en los siguietes cuatro niveles:

| **Nivel de urgencia** | **Significado** |
|:---:|:---:|
| <div style="display:inline-flex;align-items:center;justify-content:center;padding:4px 12px;border-radius:999px;background:#283539;color:#a4dad2;border:1px solid #4c6667;line-height:1;white-space:nowrap;">Leve</div> | Entre 0.1 a 3.9 en el rango de prioridades. No es prioridad, pero se debe de resolver. |
| <div style="display:inline-flex;align-items:center;justify-content:center;padding:4px 12px;border-radius:999px;background:#382e24;color:#fab35c;border:1px solid #715635;line-height:1;white-space:nowrap;">Media</div> | Entre 4.0 a 6.9 en el rango de prioridades. Debería de resolverse en menos de 12 horas. |
| <div style="display:inline-flex;align-items:center;justify-content:center;padding:4px 12px;border-radius:999px;background:#331e22;color:#eb9490;border:1px solid #6a4142;line-height:1;white-space:nowrap;">Grave</div> | Entre 7.0 a 8.9 en el rango de prioridades. Debería de resolverse en menos de 4 horas. |
| <div style="display:inline-flex;align-items:center;justify-content:center;padding:4px 12px;border-radius:999px;background:#0c0f14;color:#999999;border:1px solid #36393c;line-height:1;white-space:nowrap;">Crítica</div> | Entre 9.0 a 10.0 en el rango de prioridades. Debería de resolverse lo antes posible. |

## Heraquía de pull requests
Una pregunta común es saber ¿A dónde se deben enviar los pull requests?. Para esto se tiene la siguiente jerarquía de pull requests:


<div align="center">
	<img src="__recursos__/contributing/branchFlowChart.svg" alt="flowChartDeBranches" />
</div>


Donde:
- El celeste es la branch `main`, en donde se tiene que enviar con pull request las cosas del sufijo main.
- El azul son las branches lideres de cada área, se tiene que enviar pull request con el prefijo de cada área, por ejemplo `dev/motores`.
- El morado son las branches generales, estas pueden ser generadas por cualquier miembro.
- El naranja y amarillo corresponden a branches de estructura y administrativa. Solo administradores pueden generar estos tipos de branches.

## Código de Conducta
Favor de seguir el código de conducta del proyecto, el cual se encuentra en el archivo [CODE_OF_CONDUCT.md](CODE_OF_CONDUCT.md). Este código de conducta es importante para mantener un ambiente de trabajo respetuoso y colaborativo entre todos los miembros del equipo.