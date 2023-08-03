elvator_service yerine action kullanıldı

Action ve Service, ROS 2'de farklı tiplerdeki mesajlar kullanarak iki farklı iletişim protokolüdür. İşte Action ve Service arasındaki temel farklar:

Mesaj Yapısı:

Service: Service, tek bir istemci ve tek bir sunucu arasında tek bir istemci talebi ve sunucu yanıtı şeklinde çalışır. Service iletişimi, istemci bir talepte bulunduğunda sunucu, talebi işler ve yanıtı geri gönderir. Bu işlem tamamlandığında iletişim sonlanır.
Action: Action, istemci ve sunucu arasında uzun süreli ve ardışık çalışma süreçleri gerektiren görevlerin yürütülmesi için kullanılır. Action mesajları, üç farklı tipte mesaj içerir: goal (hedef), feedback (geribildirim) ve result (sonuç). İstemci, bir goal gönderir, sunucu goal'i işler ve geribildirimleri gönderir ve sonuç elde edildiğinde sonucu gönderir. Action iletişimi, istemci ile sunucu arasında uzun süreli sürekli etkileşim sağlar.
Süreklilik ve Etkileşim:

Service: Service çağrıları tek bir talep ve yanıt üzerinden gerçekleşir ve sürekli etkileşim sağlamaz. Service çağrıları anlık olarak gerçekleşir ve işlem tamamlandıktan sonra iletişim sonlanır.
Action: Action, uzun süreli ve ardışık bir işlem sürecini destekler. İstemci, goal gönderdiğinde sunucu bu goal'i işler ve geribildirimleri sürekli olarak gönderir. İşlem tamamlandığında sonucu döndürür ve iletişim sonlanır.
Kullanım Alanları:

Service: Service, basit ve hızlı bir şekilde bir istemci ve sunucu arasında iletişim sağlamak için kullanılır. Örneğin, veri alışverişi, ayar değişiklikleri veya basit hesaplamalar gibi işlemler için kullanılabilir.
Action: Action, daha karmaşık ve zaman alıcı görevlerin yürütülmesi için kullanılır. Örneğin, robotun bir hedefe navigasyonu, görüntü işleme gibi sürekli verilerin işlenmesi, uzaktan kumanda işlevselliği gibi uzun süreli ve ardışık işlemler için kullanılabilir.
Action ve Service, farklı senaryolara ve ihtiyaçlara göre ROS 2 uygulamalarında tercih edilebilir. Action, daha karmaşık ve etkileşimli görevlerin gerçekleştirilmesi için uygunken, Service daha basit ve anlık işlemler için tercih edilebilir.


