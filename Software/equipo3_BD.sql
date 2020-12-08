-- CREATE DATABASE equipo3;
-- USE equipo3;
-- -----------------------------------------------------
CREATE TABLE persona (
  id_persona INT NOT NULL AUTO_INCREMENT,
  nombre VARCHAR(50) NULL,
  PRIMARY KEY (id_persona)
);
-- -----------------------------------------------------
CREATE TABLE planta (
  id_planta INT NOT NULL AUTO_INCREMENT,
  tipo VARCHAR(45) NULL,
  persona_id_persona INT NOT NULL,
  PRIMARY KEY (id_planta),
  CONSTRAINT fk_planta_persona1
    FOREIGN KEY (persona_id_persona)
    REFERENCES persona (id_persona)
);    
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS lectura (
  id_lectura INT NOT NULL AUTO_INCREMENT, -- {'id_lectura':1, 'sens_luz':0,'sens_humA':23.5,'sens_tempA':25.7,'sens_humT':32,'hora':'CURRENT_TIME','fecha':'CURRENT_DATE','planta_id_planta':1}
  sens_luz INT,
  sens_humA FLOAT,
  sens_tempA FLOAT,
  sens_humT FLOAT,
  hora TIME,
  fecha DATE,
  planta_id_planta INT NOT NULL,
  PRIMARY KEY (id_lectura),
  CONSTRAINT fk_lectura_planta1
    FOREIGN KEY (planta_id_planta)
    REFERENCES planta(id_planta)
);
-- -----------------------------------------------------
insert into persona values(1,"Antonio");

insert into planta values(0,"Jitomate",1);

insert into lectura values (0,0,60,24,12,current_time,current_date,1);
insert into lectura values (0,0,60,24,12,"01:00","2000-06-19",1);
insert into lectura values (0,0,60,24,12,"01:00","2000-06-20",1);
insert into lectura values (0,0,60,24,12,"01:00","2000-07-20",1);
insert into lectura values (0,0,60,24,12,"02:00","2001-06-20",1);
insert into lectura values (0,0,60,24,12,"08:00","2000-06-20",1);
insert into lectura values (0,0,60,24,12,"12:00","2005-06-20",1);
insert into lectura values (0,0,60,24,12,"16:00:12","2000-06-30",1);
insert into lectura values (0,0,60,24,12,"16:01:21","2000-06-30",1);

select * from lectura;

delete from lectura where planta_id_planta;
SELECT 
    CURRENT_TIME AS current_date_time;

