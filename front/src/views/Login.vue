<template>
  <div class="container-login">
    <LoginCard></LoginCard>
    <p class="authors">
      <i class="bx bxl-github"></i>
      <a href="https://github.com/GUMBAUElric/6-qui-prend" target="_blank">&nbsp;Github</a>
    </p>
  </div>
</template>

<script>
import LoginCard from '@/components/LoginCard.vue'

export default {
  name: 'Login',
  components: {
    LoginCard,
  },
}
</script>

<style>
.container-login {
  width: 100%;
  height: 100vh;
  display: flex;
  flex-direction: column;
  justify-content: center;
  align-items: center;
}

.container-login .authors {
  display: flex;
  align-items: center;
}

.container-login .authors i {
  font-size: 1rem;
}

.container-login .authors {
  font-size: 0.8rem;
  margin-top: 15px;
}
</style>
