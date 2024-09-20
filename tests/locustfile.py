from locust import HttpUser, task, between

#coloque estas rutas ya que en el localhost:8089 del locust hay que colocarle el host local del server

class WebsiteUser(HttpUser):
    wait_time = between(1, 2)

    @task
    def test_sitio1(self):
        self.client.get("/sitio1/index.html")

    @task
    def test_sitio2(self):
        self.client.get("/sitio2/index.html")

    @task
    def test_sitio3(self):
        self.client.get("/sitio3/index.html")
