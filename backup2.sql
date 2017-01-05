--
-- PostgreSQL database dump
--

SET statement_timeout = 0;
SET client_encoding = 'SQL_ASCII';
SET standard_conforming_strings = on;
SET check_function_bodies = false;
SET client_min_messages = warning;

--
-- Name: plpgsql; Type: EXTENSION; Schema: -; Owner: 
--

CREATE EXTENSION IF NOT EXISTS plpgsql WITH SCHEMA pg_catalog;


--
-- Name: EXTENSION plpgsql; Type: COMMENT; Schema: -; Owner: 
--

COMMENT ON EXTENSION plpgsql IS 'PL/pgSQL procedural language';


SET search_path = public, pg_catalog;

SET default_tablespace = '';

SET default_with_oids = false;

--
-- Name: configuracion; Type: TABLE; Schema: public; Owner: postgres; Tablespace: 
--

CREATE TABLE configuracion (
    mangueras integer,
    mangueras2 integer,
    p1 integer,
    p2 integer,
    p3 integer,
    p1b integer,
    p2b integer,
    p3b integer,
    versions integer,
    ddinero integer,
    dvolumen integer,
    ppux10 integer,
    pantallas integer,
    solkm integer,
    efectivo integer
);


ALTER TABLE public.configuracion OWNER TO postgres;

--
-- Name: corte; Type: TABLE; Schema: public; Owner: postgres; Tablespace: 
--

CREATE TABLE corte (
    pk_id_corte integer NOT NULL,
    ultima_venta integer,
    t_electronico integer,
    volventat double precision,
    t_electronico2 integer,
    volventat2 double precision,
    t_electronico3 integer,
    volventat3 double precision
);


ALTER TABLE public.corte OWNER TO postgres;

--
-- Name: corte_pk_id_corte_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE corte_pk_id_corte_seq
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public.corte_pk_id_corte_seq OWNER TO postgres;

--
-- Name: corte_pk_id_corte_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE corte_pk_id_corte_seq OWNED BY corte.pk_id_corte;


--
-- Name: cuenta; Type: TABLE; Schema: public; Owner: postgres; Tablespace: 
--

CREATE TABLE cuenta (
    id_cliente integer NOT NULL,
    estado_cuenta boolean DEFAULT false,
    nombre character varying(255),
    tax_number character varying(50),
    direccion character varying(255),
    telefono character varying(30),
    ciudad character varying(50),
    provincia character varying(50),
    tipo_transaccion integer,
    saldo double precision
);


ALTER TABLE public.cuenta OWNER TO postgres;

--
-- Name: cuenta_id_cliente_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE cuenta_id_cliente_seq
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public.cuenta_id_cliente_seq OWNER TO postgres;

--
-- Name: cuenta_id_cliente_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE cuenta_id_cliente_seq OWNED BY cuenta.id_cliente;


--
-- Name: identificadores; Type: TABLE; Schema: public; Owner: postgres; Tablespace: 
--

CREATE TABLE identificadores (
    pk_idibutton integer NOT NULL,
    ibutton character varying(20) NOT NULL
);


ALTER TABLE public.identificadores OWNER TO postgres;

--
-- Name: identificadores_pk_idibutton_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE identificadores_pk_idibutton_seq
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public.identificadores_pk_idibutton_seq OWNER TO postgres;

--
-- Name: identificadores_pk_idibutton_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE identificadores_pk_idibutton_seq OWNED BY identificadores.pk_idibutton;


--
-- Name: operario; Type: TABLE; Schema: public; Owner: postgres; Tablespace: 
--

CREATE TABLE operario (
    pk_idoperario integer NOT NULL,
    nombre character varying(100),
    documento character varying(50),
    ibutton character varying(20)
);


ALTER TABLE public.operario OWNER TO postgres;

--
-- Name: operario_pk_idoperario_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE operario_pk_idoperario_seq
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public.operario_pk_idoperario_seq OWNER TO postgres;

--
-- Name: operario_pk_idoperario_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE operario_pk_idoperario_seq OWNED BY operario.pk_idoperario;


--
-- Name: precios; Type: TABLE; Schema: public; Owner: postgres; Tablespace: 
--

CREATE TABLE precios (
    fk_id_producto integer,
    precio character varying(5)
);


ALTER TABLE public.precios OWNER TO postgres;

--
-- Name: producto; Type: TABLE; Schema: public; Owner: postgres; Tablespace: 
--

CREATE TABLE producto (
    id_producto integer NOT NULL,
    descripcion character varying(50)
);


ALTER TABLE public.producto OWNER TO postgres;

--
-- Name: recibo; Type: TABLE; Schema: public; Owner: postgres; Tablespace: 
--

CREATE TABLE recibo (
    linea1 character varying(255),
    linea2 character varying(255),
    id_tax character varying(30),
    tel character varying(20),
    dir character varying(255),
    vol character varying(4),
    moneda character varying(4),
    footer character varying(255),
    logo character varying(25)
);


ALTER TABLE public.recibo OWNER TO postgres;

--
-- Name: restricciones; Type: TABLE; Schema: public; Owner: postgres; Tablespace: 
--

CREATE TABLE restricciones (
    id_vehiculo integer NOT NULL,
    id_producto integer,
    visitadia integer,
    visitasemana integer,
    visitames integer,
    volvisitadia double precision DEFAULT 0.0,
    volvisitasemana double precision DEFAULT 0.0,
    volvisitames double precision DEFAULT 0.0,
    dinvisitadia double precision DEFAULT 0.0,
    dinvisitasemana double precision DEFAULT 0.0,
    dinvisitames double precision DEFAULT 0.0,
    ppu character varying(5)
);


ALTER TABLE public.restricciones OWNER TO postgres;

--
-- Name: restricciones_id_vehiculo_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE restricciones_id_vehiculo_seq
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public.restricciones_id_vehiculo_seq OWNER TO postgres;

--
-- Name: restricciones_id_vehiculo_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE restricciones_id_vehiculo_seq OWNED BY restricciones.id_vehiculo;


--
-- Name: transaccion; Type: TABLE; Schema: public; Owner: postgres; Tablespace: 
--

CREATE TABLE transaccion (
    tipo integer NOT NULL,
    descripcion character varying(50)
);


ALTER TABLE public.transaccion OWNER TO postgres;

--
-- Name: usuario; Type: TABLE; Schema: public; Owner: postgres; Tablespace: 
--

CREATE TABLE usuario (
    pk_id_user integer NOT NULL,
    usuario character varying(20),
    pass character varying(255)
);


ALTER TABLE public.usuario OWNER TO postgres;

--
-- Name: usuario_pk_id_user_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE usuario_pk_id_user_seq
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public.usuario_pk_id_user_seq OWNER TO postgres;

--
-- Name: usuario_pk_id_user_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE usuario_pk_id_user_seq OWNED BY usuario.pk_id_user;


--
-- Name: vehiculo; Type: TABLE; Schema: public; Owner: postgres; Tablespace: 
--

CREATE TABLE vehiculo (
    id_cliente integer NOT NULL,
    id_vehiculo integer NOT NULL,
    placa character varying(20),
    serial character varying(20) NOT NULL,
    tanque double precision,
    estado_bloqueo boolean DEFAULT false,
    marca character varying(100),
    idvehiculo integer
);


ALTER TABLE public.vehiculo OWNER TO postgres;

--
-- Name: vehiculo_id_cliente_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE vehiculo_id_cliente_seq
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public.vehiculo_id_cliente_seq OWNER TO postgres;

--
-- Name: vehiculo_id_cliente_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE vehiculo_id_cliente_seq OWNED BY vehiculo.id_cliente;


--
-- Name: vehiculo_id_vehiculo_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE vehiculo_id_vehiculo_seq
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public.vehiculo_id_vehiculo_seq OWNER TO postgres;

--
-- Name: vehiculo_id_vehiculo_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE vehiculo_id_vehiculo_seq OWNED BY vehiculo.id_vehiculo;


--
-- Name: venta; Type: TABLE; Schema: public; Owner: postgres; Tablespace: 
--

CREATE TABLE venta (
    id integer NOT NULL,
    id_cliente integer NOT NULL,
    fecha timestamp without time zone DEFAULT now(),
    tipo_transaccion integer,
    dinero double precision,
    volumen double precision
);


ALTER TABLE public.venta OWNER TO postgres;

--
-- Name: venta_detalle; Type: TABLE; Schema: public; Owner: postgres; Tablespace: 
--

CREATE TABLE venta_detalle (
    fk_id integer NOT NULL,
    placa character varying(20),
    km character varying(30),
    fk_id_producto integer,
    precio double precision,
    cara integer,
    manguera integer,
    fk_id_corte integer NOT NULL,
    dinero double precision,
    volumen double precision,
    idvehiculo character varying(20)
);


ALTER TABLE public.venta_detalle OWNER TO postgres;

--
-- Name: venta_detalle_fk_id_corte_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE venta_detalle_fk_id_corte_seq
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public.venta_detalle_fk_id_corte_seq OWNER TO postgres;

--
-- Name: venta_detalle_fk_id_corte_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE venta_detalle_fk_id_corte_seq OWNED BY venta_detalle.fk_id_corte;


--
-- Name: venta_detalle_fk_id_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE venta_detalle_fk_id_seq
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public.venta_detalle_fk_id_seq OWNER TO postgres;

--
-- Name: venta_detalle_fk_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE venta_detalle_fk_id_seq OWNED BY venta_detalle.fk_id;


--
-- Name: venta_id_cliente_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE venta_id_cliente_seq
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public.venta_id_cliente_seq OWNER TO postgres;

--
-- Name: venta_id_cliente_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE venta_id_cliente_seq OWNED BY venta.id_cliente;


--
-- Name: venta_id_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE venta_id_seq
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public.venta_id_seq OWNER TO postgres;

--
-- Name: venta_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE venta_id_seq OWNED BY venta.id;


--
-- Name: pk_id_corte; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY corte ALTER COLUMN pk_id_corte SET DEFAULT nextval('corte_pk_id_corte_seq'::regclass);


--
-- Name: id_cliente; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY cuenta ALTER COLUMN id_cliente SET DEFAULT nextval('cuenta_id_cliente_seq'::regclass);


--
-- Name: pk_idibutton; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY identificadores ALTER COLUMN pk_idibutton SET DEFAULT nextval('identificadores_pk_idibutton_seq'::regclass);


--
-- Name: pk_idoperario; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY operario ALTER COLUMN pk_idoperario SET DEFAULT nextval('operario_pk_idoperario_seq'::regclass);


--
-- Name: id_vehiculo; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY restricciones ALTER COLUMN id_vehiculo SET DEFAULT nextval('restricciones_id_vehiculo_seq'::regclass);


--
-- Name: pk_id_user; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY usuario ALTER COLUMN pk_id_user SET DEFAULT nextval('usuario_pk_id_user_seq'::regclass);


--
-- Name: id_cliente; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY vehiculo ALTER COLUMN id_cliente SET DEFAULT nextval('vehiculo_id_cliente_seq'::regclass);


--
-- Name: id_vehiculo; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY vehiculo ALTER COLUMN id_vehiculo SET DEFAULT nextval('vehiculo_id_vehiculo_seq'::regclass);


--
-- Name: id; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY venta ALTER COLUMN id SET DEFAULT nextval('venta_id_seq'::regclass);


--
-- Name: id_cliente; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY venta ALTER COLUMN id_cliente SET DEFAULT nextval('venta_id_cliente_seq'::regclass);


--
-- Name: fk_id; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY venta_detalle ALTER COLUMN fk_id SET DEFAULT nextval('venta_detalle_fk_id_seq'::regclass);


--
-- Name: fk_id_corte; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY venta_detalle ALTER COLUMN fk_id_corte SET DEFAULT nextval('venta_detalle_fk_id_corte_seq'::regclass);


--
-- Data for Name: configuracion; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY configuracion (mangueras, mangueras2, p1, p2, p3, p1b, p2b, p3b, versions, ddinero, dvolumen, ppux10, pantallas, solkm, efectivo) FROM stdin;
1	1	1	2	2	3	2	2	6	0	3	0	1	1	0
\.


--
-- Data for Name: corte; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY corte (pk_id_corte, ultima_venta, t_electronico, volventat, t_electronico2, volventat2, t_electronico3, volventat3) FROM stdin;
1	0	0	0	0	0	0	0
2	66	\N	134447	\N	0	\N	0
3	66	\N	134447	\N	0	\N	0
4	66	\N	134447	\N	0	\N	0
5	76	\N	134928	\N	0	\N	0
6	77	\N	134978	\N	0	\N	0
7	78	38845	135024	\N	0	\N	0
8	79	87125	1351.26999999999998	\N	0	\N	0
9	82	16133	1354.09999999999991	\N	0	\N	0
10	92	176246	19.7899999999999991	\N	22014	\N	0
11	94	57930	20.2899999999999991	\N	22481	\N	0
12	102	175502	31.2800000000000011	\N	23268	\N	0
13	107	47948	35.6499999999999986	\N	23316	\N	0
14	111	45754	40.2199999999999989	\N	23316	\N	0
15	196	5160932	109.079999999999998	\N	41490	\N	0
16	227	2711650	123.040000000000006	\N	52905	\N	0
\.


--
-- Name: corte_pk_id_corte_seq; Type: SEQUENCE SET; Schema: public; Owner: postgres
--

SELECT pg_catalog.setval('corte_pk_id_corte_seq', 16, true);


--
-- Data for Name: cuenta; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY cuenta (id_cliente, estado_cuenta, nombre, tax_number, direccion, telefono, ciudad, provincia, tipo_transaccion, saldo) FROM stdin;
1	t	Your company 	123456789	Main street 123	7030030002	Stuttgart 	Stuttgart 	2	100000
3	t	Insepet	830071049-5	Carrera 90 No 17B 75	4222525	Bogota	Colombia 	2	168493893902
2	t	EFECTIVO	000-000	LOCAL	000-000	LOCAL	LOCAL	1	0
4	t	Elver	1546621665	carrera 157b # 145-56	6846575	bogota	cundinamarca	1	5000000
5	t	Rodrigo	3455321244	Cra 67 # 77-87 	6846575	Bogotá 	Cundinamarca 	3	5000000
6	t	Nombre de cliente	NIT / CC	Direccion	Teléfono		Departamento / Provincia	2	0
7	t	Administración Montevideo	123.456	Ruta 9 - Km. 175	(+598) 4224 1759		Maldonado	4	0
8	t	Administración Sist de Gestión	123.456	Ruta 9 - Km. 175	(+598) 4224 1759		Maldonado	1	0
9	t	admin	NIT / CC	Direccion	7567262		LOCAL	3	0
10	t	Jorge	69365452	Carrera 69b # 04-04	2256498		Bogota D.C.	3	5000000
\.


--
-- Name: cuenta_id_cliente_seq; Type: SEQUENCE SET; Schema: public; Owner: postgres
--

SELECT pg_catalog.setval('cuenta_id_cliente_seq', 1, false);


--
-- Data for Name: identificadores; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY identificadores (pk_idibutton, ibutton) FROM stdin;
1	3600000169A9ED01
2	280000011CC9F101
3	07000000C413AF02
\.


--
-- Name: identificadores_pk_idibutton_seq; Type: SEQUENCE SET; Schema: public; Owner: postgres
--

SELECT pg_catalog.setval('identificadores_pk_idibutton_seq', 6, true);


--
-- Data for Name: operario; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY operario (pk_idoperario, nombre, documento, ibutton) FROM stdin;
1	Diego Herrera	1032369729	3600000169A9ED01
2	Diego Herrera	1032369729	280000011CC9F101
3			
4	Diego Herrera 2	12345	280000011CC9F101
5	andres	CI	280000011CC9F101
\.


--
-- Name: operario_pk_idoperario_seq; Type: SEQUENCE SET; Schema: public; Owner: postgres
--

SELECT pg_catalog.setval('operario_pk_idoperario_seq', 5, true);


--
-- Data for Name: precios; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY precios (fk_id_producto, precio) FROM stdin;
1	08500
2	06500
3	03000
\.


--
-- Data for Name: producto; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY producto (id_producto, descripcion) FROM stdin;
2	DIESEL
3	PLUS
1	Corriente
0	SIN PRODUCTO
4	premium
\.


--
-- Data for Name: recibo; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY recibo (linea1, linea2, id_tax, tel, dir, vol, moneda, footer, logo) FROM stdin;
Insepet - Uniti Expo 2016	Linea 2	Hall 5 Stand C67	June 14-16 	Messe Stuttgart 	Gls 	€	Thanks for your visit	2015111202.jpg
\.


--
-- Data for Name: restricciones; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY restricciones (id_vehiculo, id_producto, visitadia, visitasemana, visitames, volvisitadia, volvisitasemana, volvisitames, dinvisitadia, dinvisitasemana, dinvisitames, ppu) FROM stdin;
1	1	1	1	1	12.5	25	100	312.5	625	2500	01000
2	4	1	1	1	26.6700000000000017	26.6700000000000017	133.330000000000013	6666.67000000000007	6666.67000000000007	33333.3300000000017	01000
\.


--
-- Name: restricciones_id_vehiculo_seq; Type: SEQUENCE SET; Schema: public; Owner: postgres
--

SELECT pg_catalog.setval('restricciones_id_vehiculo_seq', 1, false);


--
-- Data for Name: transaccion; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY transaccion (tipo, descripcion) FROM stdin;
2	CREDITO
3	PREPAGO
1	PRIVADO
4	AUTOABASTECIMIENTO
\.


--
-- Data for Name: usuario; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY usuario (pk_id_user, usuario, pass) FROM stdin;
1	admin	827ccb0eea8a706c4c34a16891f84e7b
2	diego	078c007bd92ddec308ae2f5115c1775d
3	willys	7402d37e1431288b190bdeb1a550d698
4	Camilo	6fcac41085d4fcac0472ddf8e2cdf51c
5	Camilo	838e97facf6e43f8a5c56fa1e1427d88
6	Herrera	e120ea280aa50693d5568d0071456460
7	GinoC	41e58ce2b1867981b294d50e4eaf2fb9
8	Andres Marin	f6362de27ed7590b4e32f3617451b087
9	Andres Marin	f6362de27ed7590b4e32f3617451b087
\.


--
-- Name: usuario_pk_id_user_seq; Type: SEQUENCE SET; Schema: public; Owner: postgres
--

SELECT pg_catalog.setval('usuario_pk_id_user_seq', 1, true);


--
-- Data for Name: vehiculo; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY vehiculo (id_cliente, id_vehiculo, placa, serial, tanque, estado_bloqueo, marca, idvehiculo) FROM stdin;
10	1	CIY187		100	f	Renault	79485465
10	2	NOB415	3600000169A9ED01	100	t	Renault	456897254
\.


--
-- Name: vehiculo_id_cliente_seq; Type: SEQUENCE SET; Schema: public; Owner: postgres
--

SELECT pg_catalog.setval('vehiculo_id_cliente_seq', 1, false);


--
-- Name: vehiculo_id_vehiculo_seq; Type: SEQUENCE SET; Schema: public; Owner: postgres
--

SELECT pg_catalog.setval('vehiculo_id_vehiculo_seq', 1, false);


--
-- Data for Name: venta; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY venta (id, id_cliente, fecha, tipo_transaccion, dinero, volumen) FROM stdin;
1	1	2016-10-13 14:20:20.782412	2	23026	3.06199999999999983
2	3	2015-11-12 18:45:41.464649	2	0	0
3	3	2016-10-18 12:41:05.561255	2	335	0.33500000000000002
4	3	2016-10-18 12:41:05.758376	2	335	0.33500000000000002
5	3	2016-10-18 12:43:28.655777	2	0	0
6	3	2016-10-18 12:43:29.023217	2	0	0
7	3	2016-10-18 12:43:29.628957	2	0	0
8	3	2016-10-18 12:56:07.934487	2	283	0.282999999999999974
9	3	2016-10-18 12:56:08.285337	2	283	0.282999999999999974
10	3	2016-10-18 12:56:08.872865	2	283	0.282999999999999974
11	3	2016-10-18 13:02:11.312014	2	167	0.16700000000000001
12	3	2016-10-18 13:02:11.679513	2	167	0.16700000000000001
13	3	2016-10-18 13:02:12.171165	2	167	0.16700000000000001
14	3	2016-10-18 13:02:12.707166	2	167	0.16700000000000001
15	3	2016-10-18 13:02:13.181844	2	167	0.16700000000000001
16	3	2016-10-18 13:02:13.699302	2	167	0.16700000000000001
17	3	2016-10-18 13:02:14.132367	2	167	0.16700000000000001
18	3	2016-10-18 13:02:14.534917	2	167	0.16700000000000001
19	3	2016-10-18 13:02:15.024632	2	167	0.16700000000000001
20	3	2016-10-18 13:09:09.603018	2	264	0.264000000000000012
21	3	2016-10-19 06:18:22.414828	2	796	0.796000000000000041
22	3	2016-10-19 06:19:58.740772	2	0	0
23	3	2016-10-19 11:34:12.324439	2	884	0.884000000000000008
24	3	2016-10-19 11:35:52.192471	2	518	0.518000000000000016
25	1	2016-10-19 11:42:08.645944	2	9889	1.31499999999999995
26	3	2016-01-28 15:11:58.780611	2	352	0.559000000000000052
27	3	2016-10-20 06:49:35.28676	2	4723	2.20199999999999996
28	1	2016-10-20 06:50:51.958165	2	2231	1.04000000000000004
29	3	2016-10-24 08:03:18.669764	2	8595	1.14300000000000002
30	3	2016-10-24 08:09:52.745087	2	858	0.400000000000000022
31	1	2016-11-02 09:24:31.848312	2	3888	0.517000000000000015
32	1	2016-11-02 09:25:35.999814	2	19424	2.58300000000000018
33	1	2016-11-02 09:37:16.220727	2	2918	0.388000000000000012
34	1	2016-11-02 09:38:56.027113	2	2617	0.347999999999999976
35	1	2016-11-02 09:39:39.384017	2	9144	1.21599999999999997
36	1	2016-11-02 10:47:29.200436	2	2474	0.329000000000000015
37	1	2016-11-02 10:50:55.07257	2	6196	0.823999999999999955
38	1	2016-11-02 11:02:04.437236	2	0	0
39	1	2016-11-02 11:06:57.713754	2	0	0
40	1	2016-11-02 11:07:39.139049	2	0	0
41	1	2016-11-02 11:08:23.713079	2	0	0
42	1	2016-11-02 11:10:43.154301	2	0	0
43	1	2016-11-02 11:14:08.952127	2	0	0
44	1	2016-11-02 11:18:02.773808	2	0	0
45	1	2016-11-02 11:19:23.617462	2	0	0
46	1	2016-11-02 11:20:20.351235	2	0	0
47	1	2016-11-02 12:33:28.164758	2	0	0
48	1	2016-11-02 12:34:55.655479	2	0	0
49	1	2016-11-02 12:35:29.138043	2	0	0
50	1	2016-11-02 12:44:39.036011	2	0	0
51	1	2016-11-02 12:45:39.82995	2	0	0
52	1	2016-11-02 12:46:42.391177	2	2301	0.305999999999999994
53	1	2016-11-02 12:47:13.535596	2	3632	0.482999999999999985
54	1	2016-11-02 12:47:46.233266	2	7324	0.973999999999999977
55	1	2016-11-02 12:48:37.467947	2	0	0
56	1	2016-11-02 12:57:57.295051	2	0	0
57	1	2016-11-03 15:11:06.532411	2	0	0
58	1	2016-11-03 15:11:29.172799	2	0	0
59	1	2016-11-03 15:34:19.97526	2	893	0.893000000000000016
\.


--
-- Data for Name: venta_detalle; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY venta_detalle (fk_id, placa, km, fk_id_producto, precio, cara, manguera, fk_id_corte, dinero, volumen, idvehiculo) FROM stdin;
1	BATS456	0000007	1	7520	1	1	16	23026	3.06199999999999983	\N
2	ACG226	0000080	0	0	1	0	16	0	0	\N
3	ACG226	0000000	2	1000	1	2	16	335	0.33500000000000002	\N
3	ACG226	0000000	2	1000	1	2	16	335	0.33500000000000002	\N
5	ACG226	0000000	2	0	1	2	16	0	0	\N
6	ACG226	0000000	2	0	1	2	16	0	0	\N
7	ACG226	0000000	2	0	1	2	16	0	0	\N
8	ACG226	0000000	2	1000	1	2	16	283	0.282999999999999974	\N
9	ACG226	0000000	2	1000	1	2	16	283	0.282999999999999974	\N
10	ACG226	0000000	2	1000	1	2	16	283	0.282999999999999974	\N
11	ACG226	0000000	2	1000	1	2	16	167	0.16700000000000001	\N
12	ACG226	0000000	2	1000	1	2	16	167	0.16700000000000001	\N
13	ACG226	0000000	2	1000	1	2	16	167	0.16700000000000001	\N
14	ACG226	0000000	2	1000	1	2	16	167	0.16700000000000001	\N
15	ACG226	0000000	2	1000	1	2	16	167	0.16700000000000001	\N
16	ACG226	0000000	2	1000	1	2	16	167	0.16700000000000001	\N
17	ACG226	0000000	2	1000	1	2	16	167	0.16700000000000001	\N
18	ACG226	0000000	2	1000	1	2	16	167	0.16700000000000001	\N
19	ACG226	0000000	2	1000	1	2	16	167	0.16700000000000001	\N
20	ACG226	0000000	2	1000	1	2	16	264	0.264000000000000012	\N
21	ACG226	0000000	2	1000	1	2	16	796	0.796000000000000041	\N
22	BUZZ123	0000851	2	0	1	2	16	0	0	\N
23	ACG226	0000000	2	1000	1	2	16	884	0.884000000000000008	\N
24	BUZZ123	0000000	2	1000	1	2	16	5.17999999999999972	0.518000000000000016	\N
25	BATS456	0000000	2	7520	1	2	16	9889	1.31499999999999995	\N
26	BUZZ123	0000000	1	630	1	1	16	3.52000000000000002	0.559000000000000052	\N
29	BUZZ123	0000000	1	7520	1	1	16	85.9500000000000028	1.14300000000000002	\N
31	BATS456	0000009	2	7520	1	2	16	3888	0.517000000000000015	\N
32	BATS456	0000000	2	7520	2	2	16	19424	2.58300000000000018	\N
33	BATS456	0000000	1	7520	1	1	16	2918	0.388000000000000012	\N
34	BATS456	0000000	1	7520	1	1	16	2617	0.347999999999999976	\N
35	BATS456	0000000	3	7520	2	3	16	9144	1.21599999999999997	\N
36	BATS456	0000098	1	7520	1	1	16	2474	0.329000000000000015	\N
37	BATS456	0000098	3	7520	1	3	16	6196	0.823999999999999955	\N
38	BATS456	0000000	3	0	1	3	16	0	0	\N
39	BATS456	0000000	3	0	1	3	16	0	0	\N
40	BATS456	0000000	3	0	1	3	16	0	0	\N
41	BATS456	0000000	3	0	1	3	16	0	0	\N
42	BATS456	0007854	2	0	1	2	16	0	0	\N
43	BATS456	0000000	2	0	1	2	16	0	0	\N
44	BATS456	0000009	2	0	1	2	16	0	0	\N
45	BATS456	0000009	2	0	1	2	16	0	0	\N
46	BATS456	0000000	2	0	1	2	16	0	0	\N
47	BATS456	0000000	2	0	1	2	16	0	0	\N
48	BATS456	0000000	1	0	1	1	16	0	0	\N
49	BATS456	0000000	1	0	1	1	16	0	0	\N
50	BATS456	0000000	2	0	1	2	16	0	0	\N
51	BATS456	0000000	2	0	1	2	16	0	0	\N
52	BATS456	0000000	1	7520	1	1	16	2301	0.305999999999999994	\N
53	BATS456	0000000	2	7520	1	2	16	3632	0.482999999999999985	\N
54	BATS456	0000000	3	7520	1	3	16	7324	0.973999999999999977	\N
55	BATS456	0000000	2	0	2	2	16	0	0	\N
56	BATS456	0000000	3	0	1	3	16	0	0	\N
57	123	0000000	2	0	1	2	16	0	0	\N
58	123	0000000	2	0	1	2	16	0	0	\N
59	123	0000000	2	1000	1	2	16	893	0.893000000000000016	\N
\.


--
-- Name: venta_detalle_fk_id_corte_seq; Type: SEQUENCE SET; Schema: public; Owner: postgres
--

SELECT pg_catalog.setval('venta_detalle_fk_id_corte_seq', 1, false);


--
-- Name: venta_detalle_fk_id_seq; Type: SEQUENCE SET; Schema: public; Owner: postgres
--

SELECT pg_catalog.setval('venta_detalle_fk_id_seq', 1, false);


--
-- Name: venta_id_cliente_seq; Type: SEQUENCE SET; Schema: public; Owner: postgres
--

SELECT pg_catalog.setval('venta_id_cliente_seq', 1, false);


--
-- Name: venta_id_seq; Type: SEQUENCE SET; Schema: public; Owner: postgres
--

SELECT pg_catalog.setval('venta_id_seq', 59, true);


--
-- Name: corte_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres; Tablespace: 
--

ALTER TABLE ONLY corte
    ADD CONSTRAINT corte_pkey PRIMARY KEY (pk_id_corte);


--
-- Name: cuenta_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres; Tablespace: 
--

ALTER TABLE ONLY cuenta
    ADD CONSTRAINT cuenta_pkey PRIMARY KEY (id_cliente);


--
-- Name: identificadores_ibutton_key; Type: CONSTRAINT; Schema: public; Owner: postgres; Tablespace: 
--

ALTER TABLE ONLY identificadores
    ADD CONSTRAINT identificadores_ibutton_key UNIQUE (ibutton);


--
-- Name: identificadores_pk_idibutton_key; Type: CONSTRAINT; Schema: public; Owner: postgres; Tablespace: 
--

ALTER TABLE ONLY identificadores
    ADD CONSTRAINT identificadores_pk_idibutton_key UNIQUE (pk_idibutton);


--
-- Name: operario_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres; Tablespace: 
--

ALTER TABLE ONLY operario
    ADD CONSTRAINT operario_pkey PRIMARY KEY (pk_idoperario);


--
-- Name: producto_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres; Tablespace: 
--

ALTER TABLE ONLY producto
    ADD CONSTRAINT producto_pkey PRIMARY KEY (id_producto);


--
-- Name: restricciones_id_vehiculo_key; Type: CONSTRAINT; Schema: public; Owner: postgres; Tablespace: 
--

ALTER TABLE ONLY restricciones
    ADD CONSTRAINT restricciones_id_vehiculo_key UNIQUE (id_vehiculo);


--
-- Name: transaccion_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres; Tablespace: 
--

ALTER TABLE ONLY transaccion
    ADD CONSTRAINT transaccion_pkey PRIMARY KEY (tipo);


--
-- Name: usuario_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres; Tablespace: 
--

ALTER TABLE ONLY usuario
    ADD CONSTRAINT usuario_pkey PRIMARY KEY (pk_id_user);


--
-- Name: vehiculo_idvehiculo_key; Type: CONSTRAINT; Schema: public; Owner: postgres; Tablespace: 
--

ALTER TABLE ONLY vehiculo
    ADD CONSTRAINT vehiculo_idvehiculo_key UNIQUE (idvehiculo);


--
-- Name: vehiculo_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres; Tablespace: 
--

ALTER TABLE ONLY vehiculo
    ADD CONSTRAINT vehiculo_pkey PRIMARY KEY (id_vehiculo);


--
-- Name: vehiculo_serial_key; Type: CONSTRAINT; Schema: public; Owner: postgres; Tablespace: 
--

ALTER TABLE ONLY vehiculo
    ADD CONSTRAINT vehiculo_serial_key UNIQUE (serial);


--
-- Name: venta_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres; Tablespace: 
--

ALTER TABLE ONLY venta
    ADD CONSTRAINT venta_pkey PRIMARY KEY (id);


--
-- Name: cuenta_tipo_transaccion_fkey; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY cuenta
    ADD CONSTRAINT cuenta_tipo_transaccion_fkey FOREIGN KEY (tipo_transaccion) REFERENCES transaccion(tipo);


--
-- Name: precios_fk_id_producto_fkey; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY precios
    ADD CONSTRAINT precios_fk_id_producto_fkey FOREIGN KEY (fk_id_producto) REFERENCES producto(id_producto);


--
-- Name: restricciones_id_producto_fkey; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY restricciones
    ADD CONSTRAINT restricciones_id_producto_fkey FOREIGN KEY (id_producto) REFERENCES producto(id_producto);


--
-- Name: restricciones_id_vehiculo_fkey; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY restricciones
    ADD CONSTRAINT restricciones_id_vehiculo_fkey FOREIGN KEY (id_vehiculo) REFERENCES vehiculo(id_vehiculo);


--
-- Name: vehiculo_id_cliente_fkey; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY vehiculo
    ADD CONSTRAINT vehiculo_id_cliente_fkey FOREIGN KEY (id_cliente) REFERENCES cuenta(id_cliente);


--
-- Name: venta_detalle_fk_id_corte_fkey; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY venta_detalle
    ADD CONSTRAINT venta_detalle_fk_id_corte_fkey FOREIGN KEY (fk_id_corte) REFERENCES corte(pk_id_corte);


--
-- Name: venta_detalle_fk_id_fkey; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY venta_detalle
    ADD CONSTRAINT venta_detalle_fk_id_fkey FOREIGN KEY (fk_id) REFERENCES venta(id);


--
-- Name: venta_detalle_fk_id_producto_fkey; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY venta_detalle
    ADD CONSTRAINT venta_detalle_fk_id_producto_fkey FOREIGN KEY (fk_id_producto) REFERENCES producto(id_producto);


--
-- Name: venta_id_cliente_fkey; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY venta
    ADD CONSTRAINT venta_id_cliente_fkey FOREIGN KEY (id_cliente) REFERENCES cuenta(id_cliente);


--
-- Name: venta_tipo_transaccion_fkey; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY venta
    ADD CONSTRAINT venta_tipo_transaccion_fkey FOREIGN KEY (tipo_transaccion) REFERENCES transaccion(tipo);


--
-- Name: public; Type: ACL; Schema: -; Owner: postgres
--

REVOKE ALL ON SCHEMA public FROM PUBLIC;
REVOKE ALL ON SCHEMA public FROM postgres;
GRANT ALL ON SCHEMA public TO postgres;


--
-- Name: corte; Type: ACL; Schema: public; Owner: postgres
--

REVOKE ALL ON TABLE corte FROM PUBLIC;
REVOKE ALL ON TABLE corte FROM postgres;
GRANT ALL ON TABLE corte TO postgres;


--
-- Name: corte_pk_id_corte_seq; Type: ACL; Schema: public; Owner: postgres
--

REVOKE ALL ON SEQUENCE corte_pk_id_corte_seq FROM PUBLIC;
REVOKE ALL ON SEQUENCE corte_pk_id_corte_seq FROM postgres;
GRANT ALL ON SEQUENCE corte_pk_id_corte_seq TO postgres;


--
-- Name: cuenta; Type: ACL; Schema: public; Owner: postgres
--

REVOKE ALL ON TABLE cuenta FROM PUBLIC;
REVOKE ALL ON TABLE cuenta FROM postgres;
GRANT ALL ON TABLE cuenta TO postgres;


--
-- Name: cuenta_id_cliente_seq; Type: ACL; Schema: public; Owner: postgres
--

REVOKE ALL ON SEQUENCE cuenta_id_cliente_seq FROM PUBLIC;
REVOKE ALL ON SEQUENCE cuenta_id_cliente_seq FROM postgres;
GRANT ALL ON SEQUENCE cuenta_id_cliente_seq TO postgres;


--
-- Name: producto; Type: ACL; Schema: public; Owner: postgres
--

REVOKE ALL ON TABLE producto FROM PUBLIC;
REVOKE ALL ON TABLE producto FROM postgres;
GRANT ALL ON TABLE producto TO postgres;


--
-- Name: recibo; Type: ACL; Schema: public; Owner: postgres
--

REVOKE ALL ON TABLE recibo FROM PUBLIC;
REVOKE ALL ON TABLE recibo FROM postgres;
GRANT ALL ON TABLE recibo TO postgres;


--
-- Name: restricciones; Type: ACL; Schema: public; Owner: postgres
--

REVOKE ALL ON TABLE restricciones FROM PUBLIC;
REVOKE ALL ON TABLE restricciones FROM postgres;
GRANT ALL ON TABLE restricciones TO postgres;


--
-- Name: restricciones_id_vehiculo_seq; Type: ACL; Schema: public; Owner: postgres
--

REVOKE ALL ON SEQUENCE restricciones_id_vehiculo_seq FROM PUBLIC;
REVOKE ALL ON SEQUENCE restricciones_id_vehiculo_seq FROM postgres;
GRANT ALL ON SEQUENCE restricciones_id_vehiculo_seq TO postgres;


--
-- Name: transaccion; Type: ACL; Schema: public; Owner: postgres
--

REVOKE ALL ON TABLE transaccion FROM PUBLIC;
REVOKE ALL ON TABLE transaccion FROM postgres;
GRANT ALL ON TABLE transaccion TO postgres;


--
-- Name: usuario; Type: ACL; Schema: public; Owner: postgres
--

REVOKE ALL ON TABLE usuario FROM PUBLIC;
REVOKE ALL ON TABLE usuario FROM postgres;
GRANT ALL ON TABLE usuario TO postgres;


--
-- Name: usuario_pk_id_user_seq; Type: ACL; Schema: public; Owner: postgres
--

REVOKE ALL ON SEQUENCE usuario_pk_id_user_seq FROM PUBLIC;
REVOKE ALL ON SEQUENCE usuario_pk_id_user_seq FROM postgres;
GRANT ALL ON SEQUENCE usuario_pk_id_user_seq TO postgres;


--
-- Name: vehiculo; Type: ACL; Schema: public; Owner: postgres
--

REVOKE ALL ON TABLE vehiculo FROM PUBLIC;
REVOKE ALL ON TABLE vehiculo FROM postgres;
GRANT ALL ON TABLE vehiculo TO postgres;


--
-- Name: vehiculo_id_cliente_seq; Type: ACL; Schema: public; Owner: postgres
--

REVOKE ALL ON SEQUENCE vehiculo_id_cliente_seq FROM PUBLIC;
REVOKE ALL ON SEQUENCE vehiculo_id_cliente_seq FROM postgres;
GRANT ALL ON SEQUENCE vehiculo_id_cliente_seq TO postgres;


--
-- Name: vehiculo_id_vehiculo_seq; Type: ACL; Schema: public; Owner: postgres
--

REVOKE ALL ON SEQUENCE vehiculo_id_vehiculo_seq FROM PUBLIC;
REVOKE ALL ON SEQUENCE vehiculo_id_vehiculo_seq FROM postgres;
GRANT ALL ON SEQUENCE vehiculo_id_vehiculo_seq TO postgres;


--
-- PostgreSQL database dump complete
--

