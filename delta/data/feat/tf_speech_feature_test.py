# Copyright (C) 2017 Beijing Didi Infinity Technology and Development Co.,Ltd.
# All rights reserved.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
# ==============================================================================
''' Tf speech feature unittest'''
import os
from pathlib import Path

import tensorflow as tf
from absl import logging

from delta.data.feat.speech_feature import load_wav
from delta.data.feat import tf_speech_feature as tffeat


class SpeechFeatTest(tf.test.TestCase):
  ''' tf.signal feat unittest'''

  def setUp(self):
    ''' set up '''
    main_root = Path(os.environ['MAIN_ROOT'])
    self.params = tffeat.speech_params(sr=8000, bins=40, cmvn=False)
    self.wavpath = str(
        main_root.joinpath(
            'delta/data/feat/python_speech_features/english.wav'))
    self.sr_true, self.audio_true = load_wav(str(self.wavpath), sr=8000)

  def test_extract_feature(self):
    ''' test extract feature '''
    with self.session():
      wavfile = tf.constant(self.wavpath)

      audio = tffeat.read_wav(wavfile, self.params)

      # slice and tile to batch
      audio = tf.stack([audio[:1000]] * 32)

      feature = tffeat.extract_feature(audio, self.params)

      self.assertEqual(audio.eval().shape, (32, 1000))
      self.assertAllEqual(audio.eval()[0], self.audio_true[:1000])
      self.assertEqual(feature.eval().shape, (32, 13, 40, 3))


if __name__ == '__main__':
  logging.set_verbosity(logging.INFO)
  tf.test.main()
