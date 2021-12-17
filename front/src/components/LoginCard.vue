<template>
  <div class="card">
    <img src="https://www.regledujeu.fr/wp-content/uploads/6qui-prend.png" alt="6-qui-prend-logo" />
    <div class="top">
      <h3 class="top__title">Bienvenue 👋</h3>
      <p class="top__subtitle">Veuillez entrez les identifiants de connexion</p>
    </div>
    <div class="bottom">
      <div class="form">
        <div class="form__ip" :class="ip.valid ? '' : 'form__ip--invalid'">
          <i class="bx bxs-pencil"></i>
          <input type="text" placeholder="IP du serveur" v-model="ip.msg" />
        </div>
        <div class="form__port" :class="port.valid ? '' : 'form__port--invalid'">
          <i class="bx bxs-pencil"></i>
          <input type="text" placeholder="PORT du serveur" v-model="port.msg" />
        </div>
        <div class="form__username" :class="username.valid ? '' : 'form__username--invalid'">
          <i class="bx bxs-user"></i>
          <input type="text" placeholder="Votre pseudo" v-model="username.msg" />
        </div>
      </div>
      <button class="btn" @click="login">Se connecter</button>
    </div>
  </div>
</template>

<script>
/** Import */
import { mapState } from 'vuex'

export default {
  name: 'LoginCard',
  data() {
    return {
      ip: {
        msg: '',
        valid: true,
      },
      port: {
        msg: '',
        valid: true,
      },
      username: {
        msg: '',
        valid: true,
      },
    }
  },
  computed: {
    ...mapState(['socket']),
  },
  methods: {
    login() {
      this.ip.valid = !!this.ip.msg ?? false
      this.port.valid = !!this.port.msg ?? false
      this.username.valid = !!this.username.msg ?? false
      this.username.valid = !!(this.username.msg.length > 2) ?? false

      if (!this.ip.valid || !this.port.valid || !this.username.valid) return

      this.socket.send({ ip: this.ip.msg, port: Number(this.port.msg) }, 'create-socket')
      this.socket.send(`setName ${this.username.msg}`)
    },
  },
}
</script>

<style>
.card {
  width: 500px;
  height: auto;
  background-color: #fff;
  border-radius: 0.5rem;
  box-shadow: rgba(0, 0, 0, 0.24) 0px 3px 8px;
  padding: 10px;
  display: flex;
  align-items: center;
  justify-content: center;
  flex-direction: column;
  position: relative;
}

.card img {
  width: 65px;
  position: absolute;
  top: 0;
  z-index: -1;
  transition: top 300ms ease;
}

.card .top,
.card .bottom {
  width: 100%;
  display: flex;
  align-items: center;
  justify-content: center;
  flex-direction: column;
}

.card .top .top__title {
  text-align: center;
}

.card .top .top__subtitle {
  text-align: center;
  color: var(--secondary-color);
  margin-top: -5px;
}

.card .bottom .form {
  margin: 20px 0;
  width: 50%;
}

.card .bottom .form i {
  color: var(--primary-color);
  margin: 0 5px;
}

.card .bottom .form .form__ip,
.card .bottom .form .form__port,
.card .bottom .form .form__username {
  display: flex;
  border: 1px solid var(--secondary-color);
  border-radius: 0.5rem;
  align-items: center;
  padding: 5px;
}

.card .bottom .form .form__ip--invalid,
.card .bottom .form .form__port--invalid,
.card .bottom .form .form__username--invalid {
  border-color: red;
}

.card .bottom .form .form__port {
  margin: 20px 0;
}

.card .bottom .btn {
  margin: 10px 0 20px 0;
  width: 50%;
  background-color: var(--primary-color);
  border-radius: 0.5rem;
  color: #fff;
  padding: 7px;
  cursor: pointer;
}

.card:hover img {
  top: -80px;
}
</style>
