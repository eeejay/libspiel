/* spiel-utterance.c
 *
 * Copyright (C) 2023 Eitan Isaacson <eitan@monotonous.org>
 *
 * This file is free software; you can redistribute it and/or modify it under
 * the terms of the GNU Lesser General Public License as published by the Free
 * Software Foundation; either version 2.1 of the License, or (at your option)
 * any later version.
 *
 * This file is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public
 * License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "libspiel.h"

#include "spiel-utterance.h"

/**
 * SpielUtterance:
 *
 * Represents an utterance to be spoken by a #SpielSpeaker.
 *
 * An utterance consists of the text to be spoken and other properties that
 * affect the speech, like rate, pitch or voice used.
 *
 */

struct _SpielUtterance
{
  GObject parent_instance;
};

typedef struct
{
  char *text;
  double pitch;
  double rate;
  double volume;
  SpielVoice *voice;
} SpielUtterancePrivate;

G_DEFINE_FINAL_TYPE_WITH_PRIVATE (SpielUtterance,
                                  spiel_utterance,
                                  G_TYPE_OBJECT)

enum
{
  PROP_0,
  PROP_TEXT,
  PROP_PITCH,
  PROP_RATE,
  PROP_VOLUME,
  PROP_VOICE,
  N_PROPS
};

static GParamSpec *properties[N_PROPS];

/**
 * spiel_utterance_new: (constructor)
 * @text: (not nullable): The utterance text to be spoken.
 *
 * Creates a new #SpielUtterance.
 *
 * Returns: The new #NotifyNotification.
 */
SpielUtterance *
spiel_utterance_new (const char *text)
{
  return g_object_new (SPIEL_TYPE_UTTERANCE, "text", text, NULL);
}

/**
 * spiel_utterance_get_text: (get-property text)
 * @self: a #SpielUtterance
 *
 * Fetches the text spoken in this utterance
 *
 * Returns: (transfer none): the text.
 */
const char *
spiel_utterance_get_text (SpielUtterance *self)
{
  SpielUtterancePrivate *priv = spiel_utterance_get_instance_private (self);

  return priv->text;
}

/**
 * spiel_utterance_set_text: (set-property text)
 * @self: a #SpielUtterance
 * @text: the text to assign to this utterance
 *
 * Sets the text to be spoken by this utterance
 *
 */
void
spiel_utterance_set_text (SpielUtterance *self, const char *text)
{
  SpielUtterancePrivate *priv = spiel_utterance_get_instance_private (self);
  g_free (priv->text);
  priv->text = g_strdup (text);
  g_object_notify (G_OBJECT (self), "text");
}

/**
 * spiel_utterance_get_pitch: (get-property pitch)
 * @self: a #SpielUtterance
 *
 * Fetches the pitch used in this utterance
 *
 * Returns: the pitch value.
 */
double
spiel_utterance_get_pitch (SpielUtterance *self)
{
  SpielUtterancePrivate *priv = spiel_utterance_get_instance_private (self);

  return priv->pitch;
}

/**
 * spiel_utterance_set_pitch: (set-property pitch)
 * @self: a #SpielUtterance
 * @pitch: a rate to assign to this utterance
 *
 * Sets a pitch on this utterance
 *
 */
void
spiel_utterance_set_pitch (SpielUtterance *self, double pitch)
{
  SpielUtterancePrivate *priv = spiel_utterance_get_instance_private (self);
  priv->pitch = pitch;
  g_object_notify (G_OBJECT (self), "pitch");
}

/**
 * spiel_utterance_get_rate: (get-property rate)
 * @self: a #SpielUtterance
 *
 * Fetches the rate used in this utterance
 *
 * Returns: the rate value.
 */
double
spiel_utterance_get_rate (SpielUtterance *self)
{
  SpielUtterancePrivate *priv = spiel_utterance_get_instance_private (self);

  return priv->rate;
}

/**
 * spiel_utterance_set_rate: (set-property rate)
 * @self: a #SpielUtterance
 * @rate: a rate to assign to this utterance
 *
 * Sets a rate on this utterance
 *
 */
void
spiel_utterance_set_rate (SpielUtterance *self, double rate)
{
  SpielUtterancePrivate *priv = spiel_utterance_get_instance_private (self);
  priv->rate = rate;
  g_object_notify (G_OBJECT (self), "rate");
}

/**
 * spiel_utterance_get_volume: (get-property volume)
 * @self: a #SpielUtterance
 *
 * Fetches the volume used in this utterance
 *
 * Returns: the volume value.
 */
double
spiel_utterance_get_volume (SpielUtterance *self)
{
  SpielUtterancePrivate *priv = spiel_utterance_get_instance_private (self);

  return priv->volume;
}

/**
 * spiel_utterance_set_volume: (set-property volume)
 * @self: a #SpielUtterance
 * @volume: a volume to assign to this utterance
 *
 * Sets a volume on this utterance
 *
 */
void
spiel_utterance_set_volume (SpielUtterance *self, double volume)
{
  SpielUtterancePrivate *priv = spiel_utterance_get_instance_private (self);
  priv->volume = volume;
  g_object_notify (G_OBJECT (self), "volume");
}

/**
 * spiel_utterance_get_voice: (get-property voice)
 * @self: a #SpielUtterance
 *
 * Fetches the voice used in this utterance
 *
 * Returns: (transfer none): the voice object.
 */
SpielVoice *
spiel_utterance_get_voice (SpielUtterance *self)
{
  SpielUtterancePrivate *priv = spiel_utterance_get_instance_private (self);

  return priv->voice;
}

/**
 * spiel_utterance_set_voice: (set-property voice)
 * @self: a #SpielUtterance
 * @voice: a #SpielVoice to assign to this utterance
 *
 * Sets a voice on this utterance
 *
 */
void
spiel_utterance_set_voice (SpielUtterance *self, SpielVoice *voice)
{
  SpielUtterancePrivate *priv = spiel_utterance_get_instance_private (self);
  g_clear_object (&(priv->voice));

  priv->voice = g_object_ref (voice);
  g_object_notify (G_OBJECT (self), "voice");
}

static void
spiel_utterance_finalize (GObject *object)
{
  SpielUtterance *self = (SpielUtterance *) object;
  SpielUtterancePrivate *priv = spiel_utterance_get_instance_private (self);

  g_free (priv->text);
  g_clear_object (&(priv->voice));

  G_OBJECT_CLASS (spiel_utterance_parent_class)->finalize (object);
}

static void
spiel_utterance_get_property (GObject *object,
                              guint prop_id,
                              GValue *value,
                              GParamSpec *pspec)
{
  SpielUtterance *self = SPIEL_UTTERANCE (object);

  switch (prop_id)
    {
    case PROP_TEXT:
      g_value_set_string (value, spiel_utterance_get_text (self));
      break;
    case PROP_PITCH:
      g_value_set_double (value, spiel_utterance_get_pitch (self));
      break;
    case PROP_RATE:
      g_value_set_double (value, spiel_utterance_get_rate (self));
      break;
    case PROP_VOLUME:
      g_value_set_double (value, spiel_utterance_get_volume (self));
      break;
    case PROP_VOICE:
      g_value_set_object (value, spiel_utterance_get_voice (self));
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
    }
}

static void
spiel_utterance_set_property (GObject *object,
                              guint prop_id,
                              const GValue *value,
                              GParamSpec *pspec)
{
  SpielUtterance *self = SPIEL_UTTERANCE (object);

  switch (prop_id)
    {
    case PROP_TEXT:
      spiel_utterance_set_text (self, g_value_get_string (value));
      break;
    case PROP_PITCH:
      spiel_utterance_set_pitch (self, g_value_get_double (value));
      break;
    case PROP_RATE:
      spiel_utterance_set_rate (self, g_value_get_double (value));
      break;
    case PROP_VOLUME:
      spiel_utterance_set_volume (self, g_value_get_double (value));
      break;
    case PROP_VOICE:
      spiel_utterance_set_voice (self, g_value_dup_object (value));
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
    }
}

static void
spiel_utterance_class_init (SpielUtteranceClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);

  object_class->finalize = spiel_utterance_finalize;
  object_class->get_property = spiel_utterance_get_property;
  object_class->set_property = spiel_utterance_set_property;

  /**
   * SpielUtterance:text: (getter get_text) (setter set_text)
   *
   * The utterance text that will be spoken.
   *
   */
  properties[PROP_TEXT] =
      g_param_spec_string ("text", NULL, NULL, NULL /* default value */,
                           G_PARAM_READWRITE | G_PARAM_STATIC_STRINGS);

  /**
   * SpielUtterance:pitch: (getter get_pitch) (setter set_pitch)
   *
   * The pitch at which the utterance will be spoken.
   *
   */
  properties[PROP_PITCH] = g_param_spec_double (
      "pitch", NULL, NULL, 0, 2, 1, G_PARAM_READWRITE | G_PARAM_STATIC_STRINGS);

  /**
   * SpielUtterance:rate: (getter get_rate) (setter set_rate)
   *
   * The speed at which the utterance will be spoken.
   *
   */
  properties[PROP_RATE] =
      g_param_spec_double ("rate", NULL, NULL, 0.1, 10, 1,
                           G_PARAM_READWRITE | G_PARAM_STATIC_STRINGS);

  /**
   * SpielUtterance:volume: (getter get_volume) (setter set_volume)
   *
   * The volume at which the utterance will be spoken.
   *
   */
  properties[PROP_VOLUME] =
      g_param_spec_double ("volume", NULL, NULL, 0, 1, 1,
                           G_PARAM_READWRITE | G_PARAM_STATIC_STRINGS);

  /**
   * SpielUtterance:voice: (getter get_voice) (setter set_voice)
   *
   * The voice with which the utterance will be spoken.
   *
   */
  properties[PROP_VOICE] =
      g_param_spec_object ("voice", NULL, NULL, SPIEL_TYPE_VOICE,
                           G_PARAM_READWRITE | G_PARAM_STATIC_STRINGS);

  g_object_class_install_properties (object_class, N_PROPS, properties);
}

static void
spiel_utterance_init (SpielUtterance *self)
{
  SpielUtterancePrivate *priv = spiel_utterance_get_instance_private (self);
  priv->text = NULL;
  priv->rate = 1;
  priv->volume = 1;
  priv->pitch = 1;
  priv->voice = NULL;
}
