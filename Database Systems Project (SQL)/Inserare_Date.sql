

-- Inserare date in tabelul Meniu (doar meniurile cerute)
INSERT INTO Meniu (denumire, descriere, data_inceput, data_sfarsit)
VALUES 
    ('Meniu Pranz', 'Meniu tipic pentru pranz', '2025-01-01', '2025-12-31'),
    ('Meniu Vegetarian', 'Meniu fara carne, bazat pe legume', '2025-01-01', '2025-12-31'),
    ('Meniu Copii', 'Meniu special pentru copii', '2025-01-01', '2025-12-31'),
    ('Meniu Bauturi', 'Meniu dedicat bauturilor', '2025-01-01', '2025-12-31');


-- Inserare date in tabelul Preparat (doar preparatele aferente meniurilor selectate)
INSERT INTO Preparat (id_meniu, denumire, descriere, categorie, pret) 
VALUES 
	(1, 'Supa de legume', 'Supa de legume proaspete, cu ingrediente de sezon', 'Aperitiv', 12.00),
	(1, 'Salata de muraturi', 'Salata de muraturi assortate', 'Aperitiv', 10.00),
	(1, 'Salata greceasca', 'Salata cu rosii, castraveti, masline, branza feta si ulei de masline', 'Aperitiv', 18.00),
	(1, 'Friptura de vita', 'Friptura suculenta cu garnitura de legume', 'Fel principal', 30.00),
	(1, 'Sarmale', 'Sarmale traditionale cu mamaliga', 'Fel principal', 25.00),
	(1, 'Friptura de pui cu piure de cartofi ', 'Piure moale cu piept de pui fraged', 'Fel principal', 20.00),
	(1, 'Peste la cuptor', 'Peste fragede la cuptor, cu garnitura de legume', 'Fel principal', 28.00),
	(1, 'Tiramisu', 'Desert clasic italian cu mascarpone si cafea', 'Desert', 15.00),
	(1, 'Cheesecake', 'Cheesecake cremos cu fructe de padure', 'Desert', 18.00),

-- Meniu Vegetarian
	(2, 'Guacamole cu chipsuri de porumb', 'Guacamole cremos cu chipsuri crocante de porumb', 'Aperitiv', 14.00),
	(2, 'Hummus cu legume proaspete', 'Hummus cremos cu legume crocante', 'Aperitiv', 16.00),
	(2, 'Risotto cu ciuperci si parmezan', 'Risotto cremos cu ciuperci si parmezan', 'Fel principal', 25.00),
	(2, 'Burger vegetarian cu avocado', 'Burger vegetarian cu avocado si legume proaspete', 'Fel principal', 22.00),
	(2, 'Curry de legume cu orez basmati', 'Curry picant cu legume si orez basmati', 'Fel principal', 20.00),
	(2, 'Tarta cu fructe', 'Tarta cu aluat crocant cu crema de vanilie si fructe de sezon', 'Desert', 12.00),
	(2, 'Panna cotta', 'Desert clasic italian cu crema de vanilie', 'Desert', 15.00),
	(2, 'Parfait cu iaurt si fructe', 'Parfait cu iaurt si fructe proaspete', 'Desert', 10.00),

-- Meniu Copii
	(3, 'Supa de pui', 'Supa de pui cu legume', 'Aperitiv', 10.00),
	(3, 'Cartofi prajiti', 'Cartofi prajiti crocanti si gustosi', 'Aperitiv', 8.00),
	(3, 'Friptura de pui cu piure de cartofi', 'Piept de pui fraged cu Piure de cartofi fin', 'Fel principal', 18.00),
	(3, 'Mamaliga cu branza si smantana', 'Mamaliga fina servita cu branza de vaci si smantana', 'Fel principal', 14.00),
	(3, 'Cascaval pane', 'Cascaval pane crocant, servit cu sos de rosii', 'Fel principal', 16.00),
	(3, 'Spaghete', 'Spaghete cu sos de rosii sau branza rasa', 'Fel principal', 12.00),
	(3, 'Clatite cu dulceata', 'Clatite pufoase cu gem de fructe', 'Desert', 10.00),
	(3, 'Inghetata de vanilie', 'Inghetata clasica de vanilie', 'Desert', 8.00),

-- Meniu Bauturi

    (4, 'Limonada cu menta', 'Limonada racoritoare cu menta', 'Bautura', 8.00),
    (4, 'Apa minerala', 'Apa minerala naturala', 'Bautura', 5.00),
    (4, 'Cola', 'Bautura carbogazoasa', 'Bautura', 7.00),
    (4, 'Apa plata', 'Apa plata naturala', 'Bautura', 5.00),
    (4, 'Smoothie de fructe de padure', 'Smoothie racoritor cu fructe de padure', 'Bautura', 9.00),
    (4, 'Smoothie de banane si capsuni', 'Smoothie cremos cu banane si capsuni', 'Bautura', 9.50),
    (4, 'Suc de portocale', 'Suc proaspat de portocale', 'Bautura', 6.00),
    (4, 'Suc de mere', 'Suc proaspat de mere', 'Bautura', 6.00),
    (4, 'Parfait cu iaurt si fructe', 'Parfait cu iaurt si fructe proaspete', 'Bautura', 10.00);


-- Inserare date in tabelul Comanda
-- Inserare 20 comenzi
INSERT INTO Comanda (nr_masa, data_comanda, status_comanda) 
VALUES 
    (1, '2025-01-01 10:00:00', 'In procesare'),
    (2, '2025-01-01 12:30:00', 'Finalizata'),
    (3, '2025-01-01 14:45:00', 'Finalizata'),
    (4, '2025-01-02 15:30:00', 'In procesare'),
    (5, '2025-01-02 16:00:00', 'Anulata'),
    (6, '2025-01-02 11:15:00', 'Finalizata'),
    (7, '2025-01-02 17:00:00', 'In procesare'),
    (8, '2025-01-03 13:45:00', 'Finalizata'),
    (9, '2025-01-03 09:30:00', 'In procesare'),
    (10, '2025-01-04 18:00:00', 'Finalizata'),
    (11, '2025-01-04 10:00:00', 'In procesare'),
    (12, '2025-01-04 11:30:00', 'Finalizata'),
    (13, '2025-01-04 14:00:00', 'In procesare'),
    (14, '2025-01-04 16:00:00', 'Finalizata'),
    (15, '2025-01-05 12:30:00', 'In procesare'),
    (16, '2025-01-05 10:45:00', 'Anulata'),
    (17, '2025-01-06 13:15:00', 'Finalizata'),
    (18, '2025-01-07 15:00:00', 'In procesare'),
    (19, '2025-01-07 11:00:00', 'Finalizata'),
    (20, '2025-01-07 14:30:00', 'In procesare');


-- Inserare date in tabelul Preparat_Comanda
INSERT INTO Preparat_Comanda (id_comanda, id_preparat, cantitate) 
VALUES
	(1, 1, 2),  -- Supa de leguma
	(1, 5, 1),  -- Sarmale
	(1, 28, 3), -- Cola
	(1, 33, 2), -- Suc de mere
	(1, 4, 2), -- Friptura de vita
	(1, 21, 2), -- Mamaliga cu branza
	(2, 6, 1),  -- Friptura de pui cu piure de cartofi 
	(2, 7, 1), -- Peste la cuptor
	(2, 8, 2),  -- Tiramisu
	(2, 27, 2), -- Apa minerala
	(3, 3, 2),  -- Salata greceasca
	(3, 9, 1), -- Cheesecake
	(3, 26, 2), -- Limonada cu menta
	(4, 2, 2),  -- Salata de muraturi
	(4, 4, 1),  -- Friptura de vita
	(4, 29, 1), -- Apa plata
	(5, 8, 1), -- Tiramisu
	(5, 28, 1), -- Cola
	(6, 1, 3),  -- Supa de legume
	(6, 23, 1), -- Spaghete
	(6, 22, 1), -- Cascaval pane
	(6, 7, 1), -- Peste
	(6, 15, 2),  -- Tarta cu fructe
	(7, 17, 1), -- Parfait cu iaurt si fructe
	(7, 32, 2), -- Suc de portocale
	(7, 25, 1), -- Inghetata
	(8, 13, 1), -- Burger vegetarian
	(8, 11, 1),  -- Hummus cu legume proaspete
	(8, 26, 2), -- Limonada cu menta
	(9, 6, 1),  -- Friptura de pui cu piure de cartofi 
	(9, 9, 1), -- Cheesecake
	(9, 30, 1), -- Smoothie fructe de padure
	(10, 1, 2),  -- Supa de legume
    (10, 6, 2),  -- Friptura de pui cu piure de cartofi
    (10, 9, 1),  -- Cheesecake
    (11, 4, 3),  -- Friptura de vita
    (11, 7, 2),  -- Peste la cuptor
    (11, 8, 3), -- Tiramisu
	(11, 9, 1), -- Cheesecake
	(11, 28, 2), -- Cola
	(11, 29, 4), -- Apa plata
    (12, 2, 1),  -- Salata de muraturi
    (12, 3, 1),  -- Salata greceasca
    (12, 12, 2),  -- Risotto
	(12, 32, 2), -- Suc portocale
    (13, 1, 2),  -- Supa de legume
	(13, 18, 2), -- Supa de pui
    (13, 21, 1),  -- Mamaliga cu branza
	(13, 22, 2), -- Cascaval pane
    (13, 5, 1),  -- Sarmale
    (14, 3, 2),  -- Salata greceasca
    (14, 10, 1),  -- Guacamole
	(14, 13, 1), -- Burger vegetarian
    (14, 9, 2),  -- Cheesecake
	(14, 29, 2), -- Apa plata
	(14, 30, 2), -- Smoothie fructe padure
    (15, 10, 2),  -- Guacamole 
	(15, 11, 3), -- Hummus
    (15, 7, 2),  -- Peste la cuptor
    (15, 16, 2),  -- Panna Cotta
	(15, 17, 1), -- Parfait
	(15, 30, 2), -- Smoothie fructe padure
	(15, 27, 2), -- Apa minerala
    (16, 3, 1),  -- Salata greceasca
    (16, 23, 1), -- Spaghete
    (16, 27, 2), -- Apa minerala
	(16, 25, 2), -- Inghetata
	(16, 33, 1), -- Suc de mere
	(17, 31, 3), -- Smoothie banane si capsuni
	(17, 19, 2), -- Cartofi prajiti
    (17, 13, 1), -- Burger vegetarian
	(17, 4, 1),  -- Friptura de vita
    (18, 7, 1),  -- Peste la cuptor
    (18, 8, 1), -- Tiramisu
	(18, 21, 2), -- Mamaliga cu branza
	(18, 28, 3), -- Cola
	(19, 31, 1), -- Smoothie banane si capsuni
	(19, 11, 1), -- Hummus
	(19, 7, 2),  -- Peste la cuptor
	(20, 22, 2), -- Cascaval pane
	(20, 32, 2); -- Suc portocale

-- Inserare date in tabelul Ingredient
INSERT INTO Ingredient (denumire_ingredient, descriere_ingredient, unitate)
VALUES
	('Pui', 'Carne de pui pentru ciorba', 'kg'),
    ('Legume ciorba', 'Morcovi, telina, cartofi pentru ciorba', 'kg'),
    ('Legume murate', 'Castraveti, gogosari', 'kg'),
    ('Rosii', 'Rosii dulci si zemoase', 'kg'),
    ('Castraveti', 'Castraveti proaspeti', 'kg'),
    ('Masline', 'Masline negre', 'kg'),
    ('Branza', 'Branza din lapte de vaca', 'kg'),
    ('Vita', 'Carne de vita pentru friptura', 'kg'),
    ('Legume garnitura', 'Fasole verde, morcovi, ciuperci', 'kg'),
    ('Varza murata', 'Varza murata pentru sarmale', 'kg'),
    ('Carne tocata de porc', 'Carne tocata de porc pentru umplutura sarmalelor', 'kg'),
    ('Orez', 'Orez pentru umplutura sarmalelor', 'kg'),
    ('Peste (somon, cod)', 'Peste proaspat sau congelat pentru cuptor', 'kg'),
    ('Mascarpone', 'Branza mascarpone pentru tiramisu', 'kg'),
    ('Piscoturi', 'Piscoturi pentru tiramisu', 'kg'),
    ('Cacao', 'Cacao pentru presarat deasupra tiramisului', 'kg'),
    ('Zahar', 'Zahar pentru prajituri', 'kg'),
    ('Avocado', 'Avocado proaspat pentru guacamole', 'kg'),
    ('Ceapa rosie', 'Ceapa rosie pentru guacamole', 'kg'),
    ('Naut', 'Naut pentru hummus', 'kg'),
    ('Tahini', 'Pasta de susan pentru hummus', 'kg'),
    ('Orez Risotto', 'Orez pentru risotto', 'kg'),
    ('Ciuperci', 'Ciuperci proaspete pentru risotto', 'kg'),
    ('Parmezan', 'Branza Parmezan rasa pentru risotto', 'kg'),
    ('Vin alb', 'Vin alb pentru gatit', 'l'),
    ('Chifle de burger', 'Chifle pufoase pentru burger', 'kg'),
    ('Avocado', 'Avocado proaspat pentru burger', 'kg'),
    ('Crema de vanilie', 'Crema de vanilie pentru umplutura', 'kg'),
    ('Fructe de sezon', 'Fructe de sezon pentru decor', 'kg'),
    ('Zahar brun', 'Zahar brun pentru prajituri', 'kg'),
    ('Cartofi', 'Cartofi proaspeti pentru prajit', 'kg'),
    ('Smantana', 'Smantana grasa', 'l'),
    ('Malai', 'Malai pentru sarmale', 'kg'),
    ('Lapte', 'Lapte pentru aluatul de clatite', 'l'),
    ('Oua', 'Oua pentru aluatul de clatite', 'kg'),
    ('Faina', 'Faina pentru aluatul de clatite', 'kg'),
    ('Dulceata de fructe', 'Dulceata de fructe', 'kg'),
    ('Fructe de padure', 'Fructe de padure congelate sau proaspete', 'kg'),
    ('Banane', 'Banane coapte pentru smoothie', 'kg'),
    ('Capsuni', 'Capsuni proaspete sau congelate', 'kg'),
    ('Lamaie', 'Lamaie pentru limonada', 'kg'),
    ('Menta', 'Menta proaspata pentru deserturi si bauturi', 'kg'),
    ('Miere', 'Miere naturala', 'kg'),
    ('Portocale', 'Portocale proaspete pentru suc', 'kg'),
    ('Mere', 'Mere proaspete pentru suc', 'kg'),
    ('Biscuiti digestivi', 'Biscuiti digestivi pentru crusta', 'kg'),
    ('Inghetata de vanilie', 'Inghetata clasica de vanilie, pentru desert', 'kg'),
    ('Iaurt', 'Iaurt grecesc', 'l'),
    ('Cascaval', 'Cascaval din lapte de vaca', 'kg'),
    ('Pesmet', 'Pesmet pentru cascaval pane', 'kg'),
    ('Spaghete', 'Spaghete integrale', 'kg'),
    ('Apa plata', 'Apa plata naturala pentru consum si preparate', 'l'),
    ('Apa minerala', 'Apa minerala carbogazoasa pentru consum si preparate', 'l'),
    ('Coca-Cola', 'Bautura carbogazoasa racoritoare', 'l');


-- Inserarea ingredientelor pentru preparatele selectate
INSERT INTO Ingrediente_Preparat (id_preparat, id_ingredient, cantitate)
VALUES
-- Meniu Pranz
	(1, 2, 0.4),  -- Supa de legume
	(2, 3, 0.3),  -- Salata de muraturi
	(3, 4, 0.25),  -- Salata greceasca
	(3, 5, 0.25),  -- Salata greceasca
	(3, 6, 0.2),  -- Salata greceasca
	(3, 7, 0.3),  -- Salata greceasca
	(4, 8, 0.2),  -- Friptura de vita
	(4, 9, 0.2),  -- Friptura de vita
	(5, 10, 0.25), -- Sarmale
	(5, 11, 0.5), -- Sarmale
	(5, 12, 0.15), -- Sarmale
	(6, 1, 0.4),  -- Friptura de pui cu piure de cartofi
	(6, 31, 0.3),  -- Friptura de pui cu piure de cartofi
	(7, 13, 0.35), -- Peste la cuptor
	(7, 9, 0.3), -- Peste la cuptor
	(8, 14, 0.4),  -- Tiramisu
	(8, 15, 0.3),  -- Tiramisu
	(8, 16, 0.1),  -- Tiramisu
	(8, 17, 0.1),  -- Tiramisu
	(9, 29, 0.25), -- Cheesecake
	(9, 30, 0.25), -- Cheesecake
	(9, 35, 0.25), -- Cheesecake
	(9, 36, 0.25), -- Cheesecake
	(9, 46, 0.25), -- Cheesecake
	(10, 18, 0.3),  -- Guacamole cu chipsuri de porumb
	(10, 19, 0.2),  -- Guacamole cu chipsuri de porumb
	(10, 4, 0.15),  -- Guacamole cu chipsuri de porumb
	(11, 20, 0.15),-- Hummus cu legume proaspete
	(11, 21, 0.2),-- Hummus cu legume proaspete
	(11, 9, 0.3),-- Hummus cu legume proaspete
	(12, 22, 0.5), -- Risotto cu ciuperci si parmezan
	(12, 23, 0.3), -- Risotto cu ciuperci si parmezan
	(12, 24, 0.15), -- Risotto cu ciuperci si parmezan
	(12, 25, 0.1), -- Risotto cu ciuperci si parmezan
	(13, 26, 0.35), -- Burger vegetarian cu avocado
	(13, 27, 0.2), -- Burger vegetarian cu avocado
	(13, 4, 0.1), -- Burger vegetarian cu avocado
	(14, 29, 0.3), -- Tarta cu fructe
	(14, 28, 0.35), -- Tarta cu fructe
	(14, 30, 0.2), -- Tarta cu fructe
	(15, 30, 0.2), -- Panna cotta
	(15, 29, 0.3), -- Panna cotta
	(15, 34, 0.4), -- Panna cotta
	(16, 29, 0.2), -- Parfait cu iaurt si fructe
	(16, 48, 0.35), -- Parfait cu iaurt si fructe
	(17, 1, 0.3), -- Supa de pui
	(17, 2, 0.25), -- Supa de pui
	(18, 31, 0.45), -- Cartofi prajiti
	(19, 1, 0.4), -- Friptura de pui cu piure de cartofi
	(19, 31, 0.3), -- Friptura de pui cu piure de cartofi
	(20, 33, 0.2), -- Mamaliga cu branza si smantana
	(20, 32, 0.4), -- Mamaliga cu branza si smantana
	(20, 7, 0.35), -- Mamaliga cu branza si smantana
	(21, 49, 0.3), --  Cascaval pane
	(21, 50, 0.1), --  Cascaval pane
	(22, 4, 0.2), -- Spaghete
	(22, 24, 0.2), -- Spaghete
	(22, 51, 0.35), -- Spaghete
	(23, 36, 0.4), -- Clatite cu dulceata
	(23, 30, 0.1), -- Clatite cu dulceata
	(23, 34, 0.4), -- Clatite cu dulceata
	(23, 37, 0.25), -- Clatite cu dulceata
	(24, 47, 0.4), -- Inghetata de vanilie
	(25, 42, 0.1), -- Limonada cu menta
	(25, 41, 0.5), -- Limonada cu menta
	(25, 43, 0.15), -- Limonada cu menta
	(26, 53,0.5), -- Apa minerala
	(27, 53, 0.5), -- Cola
	(28, 52,0.5), -- Apa plata
	(29, 38, 0.6), -- Smoothie de fructe de padure
	(29, 42, 0.1), -- Smoothie de fructe de padure
	(30, 39, 0.55), -- Smoothie de banane si capsuni
	(30, 40, 0.35), -- Smoothie de banane si capsuni
	(30, 43, 0.15), -- Smoothie de banane si capsuni
	(31, 44, 0.45), -- Suc de portocale
	(32, 45, 0.45); -- Suc de mere





