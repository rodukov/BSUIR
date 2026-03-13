-- 1. Ускорение поиска пользователей по ФИО (частый сценарий в админ-панели)
CREATE INDEX idx_users_last_first_name ON users (last_name, first_name);

-- 2. Ускорение поиска товаров по названию (для поиска в каталоге)
-- Используем расширение pg_trgm, если нужен поиск по части слова, 
-- но здесь создадим обычный B-tree для префиксного поиска.
CREATE INDEX idx_products_name ON products (product_name);

-- 3. Индексы на внешние ключи
CREATE INDEX idx_users_role_id ON users (role_id);
CREATE INDEX idx_products_category_id ON products (category_id);
CREATE INDEX idx_products_brand_id ON products (brand_id);
CREATE INDEX idx_orders_customer_id ON orders (customer_id);

-- 4. Ускорение поиска по датам (отчеты по продажам и поставкам)
CREATE INDEX idx_orders_order_date ON orders (order_date);
CREATE INDEX idx_deliveries_delivery_date ON deliveries (delivery_date);

-- 5. Поиск активных скидок (фильтрация по диапазону дат)
CREATE INDEX idx_discounts_dates ON discounts (start_date, end_date);

-- 6. Оптимизация поиска по статусу заказа
-- Полезно, если нужно быстро найти все заказы в статусе 'в обработке'
CREATE INDEX idx_orders_status ON orders (status);
