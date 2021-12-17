<template>
  <transition name="modal">
    <div class="modal-mask">
      <div class="modal-wrapper">
        <div class="modal-container">
          <div class="modal-header">
            <h3>Fin de partie</h3>
          </div>
          <div class="modal-body">
            <div class="rank" v-for="player in playersScore" :key="player.uid">
              <img src="https://cdn-icons-png.flaticon.com/512/625/625398.png" alt="" />
              <p>{{ player.name }} : {{ player.points }}</p>
            </div>
          </div>
          <div class="modal-footer">
            <button class="btn" @click="$emit('close')">OK</button>
          </div>
        </div>
      </div>
    </div>
  </transition>
</template>

<script>
/** Import */
import { mapState } from 'vuex'

export default {
  name: 'Modal',
  computed: {
    ...mapState(['playersScore']),
  },
}
</script>

<style>
.modal-mask {
  position: fixed;
  z-index: 9998;
  top: 0;
  left: 0;
  width: 100%;
  height: 100%;
  background-color: rgba(0, 0, 0, 0.5);
  display: table;
  transition: opacity 0.3s ease;
}

.modal-wrapper {
  display: table-cell;
  vertical-align: middle;
}

.modal-container {
  width: 300px;
  margin: 0px auto;
  padding: 20px 30px;
  background-color: #fff;
  border-radius: 2px;
  box-shadow: 0 2px 8px rgba(0, 0, 0, 0.33);
  transition: all 0.3s ease;
}

.modal-header {
  width: 100%;
}

.modal-header h3 {
  margin-top: 0;
  text-align: center;
}

.modal-body {
  margin: 10px 0;
}

.modal-body .rank {
  display: flex;
  justify-content: center;
  align-items: center;
}

.modal-body .rank img {
  width: 30px;
}

.modal-body .rank p {
  margin-left: 10px;
}

.modal-default-button {
  float: right;
}

.modal-footer {
  display: flex;
  justify-content: center;
  align-items: center;
}

.modal-footer .btn {
  background-color: var(--primary-color);
  width: 80px;
  padding: 3px;
  color: #fff;
  border-radius: 2rem;
  cursor: pointer;
}

/*
 * The following styles are auto-applied to elements with
 * transition="modal" when their visibility is toggled
 * by Vue.js.
 *
 * You can easily play with the modal transition by editing
 * these styles.
 */

.modal-enter {
  opacity: 0;
}

.modal-leave-active {
  opacity: 0;
}

.modal-enter .modal-container,
.modal-leave-active .modal-container {
  -webkit-transform: scale(1.1);
  transform: scale(1.1);
}
</style>
